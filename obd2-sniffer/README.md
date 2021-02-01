# OBD2 Sniffer

For reverse engineering the data format of the RAM Promaster City CAN Bus.

Following the guide at: https://www.carloop.io/apps/app-socketcan/

# Codes

These are what I have found to be true with my vehicle, you should verify
any information on this page with your own vehicle.

## Brakes

Brake Pedal:

Byte 0 corrosponds with braking pressure, linear from 00 to probably FF, 77 is me pressing really hard
`2E2 [00] 00 00 00 ...`

This byte also seems to look at braking

```
NO BRAKES    1E8 00 00 00 0B 96
LIGHT BRAKES 1E8 00 00 04
MORE BRAKES  1E8 00 00 06
```

## Acceleration

A lot of things move with accelerator pedal

Pedal depression while parked:

```
ENGINE OFF 1F8 C2 51 [00] 4A 21 XX XX XX
IDLE       1F8 01 F4 [00] 3E 82 XX XX XX
2000 RPM   1F8 01 F6 [0C] 3C A2 AC XX XX
```

Byte 2 is pedal depression, from 00 to FF probably

## Steering Wheel

Not sure if this would allow us to publish to turn the wheels by wire,
this more likely just reads steering wheel orientation.

```
TURNED RIGHT   1EE  08 23 37 D0 xx xx
STRAIGHT       1EE  1C 3E 37 D0 xx xx
TURNED LEFT    1EE  30 95 37 D0 xx xx
```

## Transmission

Transmission engaged?

```
P AND N 4D8  09 E0 BA 00 00 00 5D [50]
R AND D 4D8  09 E0 BA 00 00 00 5D [82]
```

## Speed

```
PARKED 1F0  00 00 [00 00] 24 00 0E 9A  // 0
10MPH  1F0  00 00 [02 38] 24 00 0E 9A  // 568   16km/h
20MPH  1F0  00 00 [03 DE] 24 00 0E 9A  // 990   32km/h
30MPH  1F0  00 00 [05 FC] 24 00 0E 9A  // 1532  48km/h
```

2E4 and 2E6 also look related to speed, they behave similarly

```
PARKED  2E4  00 00 00 00 00 00 00 0A  // 0
SLOW    2E4  01 06 80 83 C0 80 0F A0  //
10MPH   2E4  04 3F 82 21 42 20 0E 0A  // 16km/h
20MPH   2E4  07 29 03 A0 C3 90 04 04  // 32km/h
```

## Parking Brake

```
OFF: 0.000000 4E0 00 00 40 68 00 00 00 F6 ..@h....
ON:  0.000000 4E0 00 00 40 68 00 00 20 F6 ..@h.. .
```

## Wiper Blade

```
OFF 0.000000 3E4 C8 01 75 00 00 00 ..u...
ON  0.408831 3E4 C8 03 75 00 00 00 ..u...
```

## Electronic Traction Control Display Setting

```
ON (default)   0.000000 4E4 00 00 00 00 00 0A 00 07 ........
OFF            0.000000 4E4 00 00 80 00 00 0A 00 07 ........
```

## Doors

Drivers Door

```
CLOSED  0.000000 4E0 00 00 40 68 00 00 20 F6 ..@h.. .
OPEN    0.000000 4E0 00 00 48 68 00 00 20 F6 ..@h.. .
```

Other doors did not seem to trigger any CAN messages

## Unknown

1E6 first 5 bytes look like a rotary encoder, advances forward in D or backward in R. Seems to be independent of engine since it still works when wheels turn in N
1E6 byte 6 might be 'in motion', turns to F0 when going fwd or back and 0 in neutral and braking
