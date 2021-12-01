# Notes on _Computer System: A Programmer's Perspetive_

Author: Junjia Wang

Date: Since 28 Nov 2021

## 1. Computer Network

### Basic of Network

Type1: Host(Adapter) -> Hub(1Mbps) -> Bridge(1Gbps) = LAN

Type2 : Host + Host = LAN -> Router + Router = WAN

Internet Protocol will define:

* Naming Scheme
* Delivery Mechanism

Data Transformation from Host A to Host B

LAN1 Frame Header: to router

Frame include internet Header: to Host B

Router fetch internet Header,  then create a new LAN2 Frame Header, to Host B, forward it to LAN2 adapter

LAN2 adapter forward it to host B, then protocol software strips off the two headers, send it to server's address

### The Global IP Intenet

IP Protocol: unreliable, from host to host

UDP(Unreliable Datagram Protocol): extended IP, from process to process

Internet Properties:

* The set of hosts is mapped to a set of 32-bit *IP addresses.*
* The set of IP addresses is mapped to a set of identifiers called *Internet domain names.*
* A process on one Internet host can communicate with a process on any other Internet host over a *connection*.

IPv4 vs Ipv6

* The original Internet protocol, with its 32-bit addresses, is known as Internet Protocol Version 4 (IPv4).
* Internet Protocol Version 6 (IPv6), that uses 128-bit addresses and that was intended as the successor to IPv4.

IP address presented:

0x8002c2f2 = 128.2.194.242 (dotted-decimal representation)

### Domain

ICANN in charge of first-level domain

