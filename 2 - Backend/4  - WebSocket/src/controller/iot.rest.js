import { Router } from "express";
import * as database from "../database/mock.connector.js";
import * as socket from "./iot.socket.js"

const router = Router();

router.get("/data", async (req, res) => {
  const data = await database.getMeasurementData();

  res.status(200).json({ status: "ok", data });
});

router.post("/data", async (req, res) => {
  const data = await database.addMeasurementData(req.body);

  socket.broadcastMeasurementData(data);
  
  res.status(200).json({ status: "ok" });
});

export default router;
