import { Router } from "express";

const router = Router();

router.get("/data", async (req, res) => {
  console.log({ ...req.query });
  console.log({ ...req.body });

  res.status(200).json({ status: "ok" });
});

router.post("/data", async (req, res) => {
  console.log({ ...req.query });
  console.log({ ...req.body });

  res.status(200).json({ status: "ok" });
});

export default router;
