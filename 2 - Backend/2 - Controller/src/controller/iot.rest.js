import { Router } from "express";

const router = Router();

router.get("/data", async (req, res) => {

  try {
    console.log({ ...req.query }); 
    console.log({ ...req.body });

    res.status(200).json({ status: "success" });
  } catch (error) {
    res.status(400).json({ status: "error", message: error.message });
  }
});

router.post("/data", async (req, res) => {

  try {
    console.log({ ...req.query }); 
    console.log({ ...req.body });

    res.status(201).json({ status: "success" });
  } catch (error) {
    res.status(400).json({ status: "error", message: error.message });
  }
});

export default router;
