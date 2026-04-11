import cors from "cors";
import express from "express";

const app = express();

app.use(cors());
app.use(express.json());

app.get("/api/v1/health", (req, res) => {
  res.json({ status: "online" });
});

export default app;
