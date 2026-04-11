import cors from "cors";
import express from "express";
import iotRoutes from "./controller/iot.rest.js";

const app = express();

app.use(cors());
app.use(express.json());

app.use("/api/v1/iot", iotRoutes);

app.get("/api/v1/health", (req, res) => {
  res.json({ status: "online" });
});

export default app;
