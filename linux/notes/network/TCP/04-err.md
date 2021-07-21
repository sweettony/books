## Write to a socket closed by peer
- first  write trigger RST 
- second write **signal(SIGPIPE)** is sent to process.
  if signal is ignore or return form signal handler, write return **EPIPE**.

<p></br></p>

## Read from a socket closed by peer
- return 0 indicate read EOF.


<p></br></p>

## Crashing of server host
- SO_KEEPALIVE 
- When the server host crashes, nothing is sent out on the  
  existing network connections. That is, we are assuming  
  the host crashes and is not shut down by an operator.  
  If we watch the network with tcpdump, we will see the  
  client TCP continually retransmitting the data segment,   
  trying to receive an ACK from the server. Section 25.11  
  of TCPv2 shows a typical pattern for TCP retransmissions:    
  Berkeleyderived implementations retransmit the data segment  
  12 times, waiting for around 9 minutes before giving up.  
  When the client TCP finally gives up (assuming the server  
  host has not been rebooted during this time, or if the server  
  host has not crashed but was unreachable on the network, assuming  
  the host was still unreachable), an error is returned to the  
  client process. Since the client is blocked in the call to  
  readline, it returns an error. Assuming the server host crashed  
  and there were no responses at all to the client’s data segments,  
  the error is ETIMEDOUT. But if some intermediate router  
  determined that the server host was unreachable and responded  
  with an ICMP ‘‘destination unreachable’’ message, the error  
  is either EHOSTUNREACH or ENETUNREACH.
- If have timeout, we will detect error quicker than having  
  to wait nine minutes.

## Crashing and Rebooting of server host
- the server is reboot and the client is not aware that.
- when the client write data to server and server reply **RST**
- when client read buff, the read return ECONNREST

