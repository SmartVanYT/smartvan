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
  if (parts.length != 3) {
    console.error("Payload malformed:", payload);
    throw 'malformed payload';
  }

  const version = parseInt(parts[0]);
  const device_ts = parseInt(parts[1]);
  const tempF = parseFloat(parts[2]);

  if (version != 0) {
    console.error("Version mismatch:", version);
    throw 'version mismatch';
  }

  return {
    device_id: device_id.slice(0, 4),
    device_ts: device_ts,
    server_ts: receive_ts,
    payload_version: version,
    temperature_f: tempF,
  };
}

function printQueryErrorDetails(err) {
  if (!err) {
    return;
  }

  console.error('Query Error:', JSON.stringify(err));
}

exports.main = function (event, context) {
  try {
    const decodedData = decodeEvent(event);

    // Instantiates a client
    const bigquery = BigQuery({
      projectId: projectId
    });

    // Inserts data into a table
    const rows = [decodedData];
    rows.forEach((row) => console.log('Will insert: ', row));

    bigquery
      .dataset(datasetId)
      .table(tableId)
      .insert(rows)
      .then((resp) => {
        console.log("Did insert rows with response:", resp);
        if (resp && resp.errors) {
          resp.errors.forEach((err) => printQueryErrorDetails(err));
        }
      }).catch((e) => {
        console.error("BigQuery threw error:", e);
        printQueryErrorDetails(e);
      });
  } catch (e) {
    console.error("Exception:", e);
    console.log("Event:", event, "Context:", context);
  }
};
