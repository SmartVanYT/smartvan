/**
 * Triggered from a message on a Cloud Pub/Sub topic.
 *
 * @param {!Object} event Event payload.
 * @param {!Object} context Metadata for the event.
 */
Date.prototype.toUnixTime = function () { return this.getTime() / 1000 | 0 };
Date.time = function () { return new Date().toUnixTime(); }

const BigQuery = require('@google-cloud/bigquery');
const package = require('./package.json');

// Be sure to customize package.json
const projectId = package.config.project_id;
const datasetId = package.config.dataset_id;
const tableId = package.config.table_id;

function decodeEvent(event) {
  // These are sent to us from Particle
  const attributes = event.attributes;
  const device_id = attributes.device_id;
  const receive_ts = new Date(attributes.published_at).toUnixTime();

  // Cloud pubsub puts this in as base64
  const iotData = Buffer.from(event.data, 'base64').toString();
  const parts = iotData.split(",");
  if (parts.length != 4) {
    console.error("Payload malformed:", new Error('malformed payload: ' + payload));
    throw 'malformed payload';
  }

  const version = parseInt(parts[0]);
  const device_ts = parseInt(parts[1]);
  const tempF = parseFloat(parts[2]);
  const engine_state = parseInt(parts[3]);

  if (version != 0) {
    console.error("Version mismatch:", new Error('version mismatch: ' + version));
    throw 'version mismatch';
  }

  return {
    device_id: device_id.slice(0, 4),
    device_ts: device_ts,
    server_ts: receive_ts,
    payload_version: version,
    temperature_f: tempF,
    engine_state: engine_state,
  };
}

function printQueryErrorDetails(err) {
  if (!err) {
    return;
  }

  console.error('Query Error:', JSON.stringify(err));
}

exports.main = function (event, _context, callback) {
  var decodedData = {};
  try {
    decodedData = decodeEvent(event);
  } catch (e) {
    console.error("Error decoding, skipping:", e);
    callback(); // this is likely a programmer error and should not be retried
    return;
  }

  const row = {
    insertId: decodedData.device_ts + decodedData.server_ts,
    json: decodedData,
  };
  const options = { raw: true };
  console.log('Will insert', row);

  try {
    BigQuery({ projectId: projectId })
      .dataset(datasetId)
      .table(tableId)
      .insert(row, options,)
      .then((resp) => {
        console.log("Did insert rows with response:", resp);
        callback();
      }).catch((e) => {
        console.error("BigQuery threw error:", e);
        printQueryErrorDetails(e);
        callback(e);
      });
  } catch (e) {
    console.error("Forwarding Exception:", e);
    console.log("Event:", event);
    callback(e);
  }
};
