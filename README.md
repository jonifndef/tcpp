# tcpp

## Tell me some goals that sound good
- No ipv6
- Dunno

## So, what the deal with RFC:s?
[RFC7414](https://datatracker.ietf.org/doc/html/rfc7414#section-2) is something of a list of RFC:s that you might want or not want to implement.

## List of RFC:s we probably want to implement:
- [RFC793](https://datatracker.ietf.org/doc/html/rfc793#section-3.1) - Core functionality (Is this deprecated, which would be better to use?)
- [RFC1122](https://datatracker.ietf.org/doc/html/rfc1122) - Congestion control
- [RFC791](https://datatracker.ietf.org/doc/html/rfc791) - The IP Protocol

## Nice to haves:
- [RFC2398](https://datatracker.ietf.org/doc/html/rfc2398) - Testing tools
- [RFC2525](https://datatracker.ietf.org/doc/html/rfc2525) - Known problems, debug help

## Other tips and tricks:

To set capabilities, run:
```sudo setcap CAP_NET_ADMIN=ep my_binary```

To set tap interface in up state, run:
```sudo ip link set my_tap_interface up```

To set ip addr for interface, run:
```sudo ip addr add x.x.x.x/netmask dev my_tap_interface```
