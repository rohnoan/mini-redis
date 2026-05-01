FULL PROJECT ROADMAP (STRICT ORDER)
PHASE 1 — CORE SERVER (no logic, just networking)
TCP server
Accept 1 client
Read data from socket
Send response back

Output: echo server (whatever client sends → return back)

PHASE 2 — COMMAND PIPELINE

Flow:

Client → Parser → Store → Response

Build:

Parser (string → command + args)
Store (unordered_map)
Integrate both

Commands:

SET key value
GET key
DEL key
PHASE 3 — MULTI CLIENT
thread per client
client_handler module used here
PHASE 4 — THREAD SAFETY
mutex on store
avoid race conditions
PHASE 5 — TTL (expiry)
store expiry time
background cleaner OR lazy delete
PHASE 6 — PERSISTENCE (AOF)
log every write
reload on restart
PHASE 7 — ADVANCED (optional)
epoll
pipelining
sharding
SYSTEM FLOW (REMEMBER THIS)
Client
  ↓
Server (accept)
  ↓
Client Handler (thread)
  ↓
Parser
  ↓
Store
  ↓
Response

If this is not clear → stop. Everything depends on this.