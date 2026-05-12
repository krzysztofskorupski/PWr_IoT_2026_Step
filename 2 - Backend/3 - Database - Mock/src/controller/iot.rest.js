import { Router } from "express";
import * as database from "../database/mock.connector.js";

const router = Router();

router.get("/data", async (req, res) => {
  const data = await database.getMeasurementData();

  res.status(200).json({ status: "ok", data });
});

router.post("/data", async (req, res) => {
  const data = await database.addMeasurementData(req.body);

  res.status(200).json({ status: "ok" });
});

export default router;
