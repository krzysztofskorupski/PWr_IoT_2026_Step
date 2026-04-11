import http from "http";
import app from "./app.js";

const server = http.createServer(app);

server.listen(3000, "0.0.0.0", async () => {
  console.log(`Backend running on: http://0.0.0.0:3000`);
});
