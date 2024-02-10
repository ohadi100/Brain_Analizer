## Desired final directory tree of brain:

### 1. Brain

1.1 Brain

1.2 Config 

1.2.1 JSON files

1.2.2 Constants


### 2. Sensor communicator

2.1 Communicator

2.2 ViWi communicator (derived)

2.3 SOME/IP-GSDP communicator  (derived)


### 3. Sensor data

3.1 Sensor data (derived from common)

3.2 Derived (CAN, Network, Host)


### 4. Sensor notification handler

4.1 Sensor notification handler factory (creates handlers)

4.2 Sensor notification handler (derived from common)

4.3 Derived (per sensor)

4.4 Internal data streamer (previously Internal_player)

4.4.1 Internal data streamer

4.4.2 Derived (per sensor)


### 5. Data queue handler (previously controller)

5.1 Data queue handler factory (creates handlers, WRR)

5.2 Data queue handler

5.3 Derived


### 6. Rule engine  (previously engines)

6.1 Rule engine

6.2 Derived

6.3 Counter (derived from common)


### 7. Events


### 8. Sender (previously Shaper)

8.1 Sender Storage (mapper, queues)

8.2 Preparator (WRR)

8.2.1 Creditor

8.3 Publisher (derived from common)

8.4 BE logic (Ack reporter & retransmission) (previously ShaperCommThresholds)


### 9. Noise filter


### 10. Utils

10.1 Weighted Round Robin (WRR)

10.2 Ipv6Address

10.3 Vehicle_data (called by shaper)

10.4 Logger

10.4.1 Logger (derived from common)

10.4.2 HTTP_server

10.4.2.1 Server interface

10.4.2.2 Derived
