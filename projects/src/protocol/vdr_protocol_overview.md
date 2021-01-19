![InfinityLabs Logo](https://infinitylabs.co.il/wp-content/themes/infinity/images/logo.png)

# VDR Protocol

## Motivation

- Introduction to communication protocols
- Build a simple protocol for communication between master and minions

## Requirements

- Meant to be used with UDP
- Works with blocks (4k)
- For simplicity, work with bytes granularity
- Use pragma pack to avoid padding

## Presentation

- Request
  - Header
    - type: 8 bits
    - uid: 64 bits
    - block index: 64 bits
  - Write request only: block of data

- Reply
  - Header
    - type: 8 bits
    - request uid: 64 bits
    - error code: 8 bits
  - Read request only: block of data

## Notes

- Is a byte always 8 bits ?
  - Officially no. But a lot of protocols depend on it today. Even if it's possible to build a different architecture. A lot of things won't be compatible. It became standard. So even if we pretty can rely on the fact that `char` will always be 8 bits, using `uint8_t` (or `u_int8_t`) will bring compilation error in case of I try to run this protocol on an architecture with a byte different from 8 bits, in case of runtime bugs.

## Implementation

- VDR Protocol: [click here](vdr_protocol.hpp)

## Questions

---
<footer style="color:#00078C">
&copy;InfinityLabs R&D

<div id="date">
<script>
var d = new Date();
document.getElementById("date").innerHTML = d.toDateString();
</script>
</div>

</footer>