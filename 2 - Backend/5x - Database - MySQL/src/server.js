import http from "http";
import app from "./app.js";
import { initWebSocket } from "./controller/iot.socket.js";
import { initDatabase } from "./database/mysql.connector.js";

const server = http.createServer(app);

server.listen(3000, "0.0.0.0", async () => {
  initDatabase()
  initWebSocket(server);
  console.log(`Backend running on: http://0.0.0.0:3000`);
});
