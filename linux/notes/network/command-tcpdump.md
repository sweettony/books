## tcpdump

## tcp flags
|Value|Flag Type|Description|
|:--|:--|:--|
|S|SYN|Connection Start|
|F|FIN|Connection Finish|
|P|PUSH|Data push|
|S|RST|Connection reset|
|.|ACK|Acknowledgment|

## tcp connection start-up and finish  

15:33:43.867979 IP localhost.6061 > localhost.6060: Flags [S], seq 1729612972, win 43690, options [mss 65495,sackOK,TS val 23290672 ecr 0,nop,wscale 7], length 0  
15:33:43.867993 IP localhost.6060 > localhost.6061: Flags [S.], seq 2220342477, ack 1729612973, win 43690, options [mss 65495,sackOK,TS val 23290672 ecr 23290672,nop,wscale 7], length 0  
15:33:43.868017 IP localhost.6061 > localhost.6060: Flags [.], ack 1, win 342, options [nop,nop,TS val 23290672 ecr 23290672], length 0  
15:33:48.953096 IP localhost.6061 > localhost.6060: Flags [F.], seq 1, ack 1, win 342, options [nop,nop,TS val 23295756 ecr 23290672], length 0  
15:33:48.953181 IP localhost.6060 > localhost.6061: Flags [.], ack 2, win 342, options [nop,nop,TS val 23295757 ecr 23295756], length 0  
15:33:48.953323 IP localhost.6060 > localhost.6061: Flags [F.], seq 1, ack 2, win 342, options [nop,nop,TS val 23295757 ecr 23295756], length 0  
15:33:48.953341 IP localhost.6061 > localhost.6060: Flags [.], ack 2, win 342, options [nop,nop,TS val 23295757 ecr 23295757], length 0  