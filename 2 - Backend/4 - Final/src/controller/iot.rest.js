import { Router } from "express";
import * as database from "../database/mock.connector.js";

const router = Router();

router.get("/device", async (req, res) => {

  try {
    const data = await database.getUniqueDeviceData();

    res.status(200).json({ status: "success", data });
  } catch (error) {
    sendError(res, error);
  }
});

router.get("/data", async (req, res) => {

  try {
    const { device } = req.query;

    const data = await database.getMeasurementData(device);

    res.status(200).json({ status: "success", data });
  } catch (error) {
    sendError(res, error);
  }
});

router.post("/data", async (req, res) => {

  try {
    await database.addMeasurementData(req.body);

    res.status(201).json({ status: "success" });
  } catch (error) {
    sendError(res, error);
  }
});

const sendError = (res, error, statusCode = 400) => {
  res.status(statusCode).json({ status: "error", message: error.message });
};

export default router;
