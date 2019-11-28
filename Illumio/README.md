#NAT Coding Challenge

## Design

Using the unordered map container to store the mapping of source <ip:port> pair to destination <ip:port> pair. Using the vector container to store the input flows.

Assume that the upper lines in the NAT file is latest. Therefore, if a line in flow file matches with multiple source <ip:port> pairs in input file, it should follows the latest one (the upper line in the file). 

To identify which rule should be selected, add an int variable to indicate the row numbers of rules in NAT file. If a source <ip:port> pair matches with multiple rules, the rule with smallest row number should be applied.

## Test

Case 1:
input.txt:
10.0.1.1:8080,192.168.0.1:80
10.0.1.1:8084,192.168.0.2:8080
10.0.1.1:8086,192.168.0.4:80
10.0.1.1:8082,192.168.0.3:80
10.0.1.2:8080,1.1.1.1:1
\*:21,1.2.3.4:12
10.11.12.13:\*,40.100.20.7:3389

flow.txt:
10.0.1.1:8080
5.6.7.8:55555
10.0.1.1:8086
9.8.7.6:21
10.1.1.2:8080
34.65.12.9:22
10.0.1.2:8080

output:
10.0.1.1:8080 -> 192.168.0.1:80
No nat match for5.6.7.8:55555
10.0.1.1:8086 -> 192.168.0.4:80
9.8.7.6:21 -> 1.2.3.4:12
No nat match for10.1.1.2:8080
No nat match for34.65.12.9:22
10.0.1.2:8080 -> 1.1.1.1:1

Case 2:
input.txt:
\*:8080,1.1.1.1:1
10.0.1.1:8080,192.168.0.1:80
10.0.1.2:8080,1.1.1.1:2

flow.txt:
10.0.1.1:8080
10.0.1.2:8080

output:
10.0.1.1:8080 -> 1.1.1.1:1
10.0.1.2:8080 -> 1.1.1.1:1

Case 3:
input.txt:
10.0.1.1:\*,40.100.20.7:3389
10.0.1.1:8080,192.168.0.1:80
10.0.1.2:8080,1.1.1.1:2

flow.txt:
10.0.1.1:8080
10.0.1.2:8080

output:
10.0.1.1:8080 -> 40.100.20.7:3389
10.0.1.2:8080 -> 1.1.1.1:2

Case 4:
input.txt:
10.0.1.1:\*,40.100.20.7:3389
\*:8080,1.1.1.1:1
10.0.1.1:8080,192.168.0.1:80
10.0.1.2:8080,1.1.1.1:2

flow.txt:
10.0.1.1:8080
10.0.1.2:8080

output:
10.0.1.1:8080 -> 40.100.20.7:3389
10.0.1.2:8080 -> 1.1.1.1:1

## Refinements

Firstly, this simple code is design with the assumption that all input are in the right format. If I have more time, the identification of wrong format input should be identified, including containing \* in the destination <ip:port> pairs.
