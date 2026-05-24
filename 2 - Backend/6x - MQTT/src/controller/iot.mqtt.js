import mqtt from "mqtt";
import * as database from "../database/mysql.connector.js";
import * as socket from "./iot.socket.js";

const mqtt_topic = "iot/data";

export const initMqtt = async () => {
  const client = mqtt.connect("mqtt://localhost:1883", {
    clientId: "Backend_IoT_Controller",
  });

  client.on("connect", () => {
    client.subscribe(mqtt_topic, (err) => {
      if (!err) {
        console.log(`MQTT connection established (topic: ${mqtt_topic})`);
      } else {
        console.error(`MQTT connection failed${err.message ? `:${err.message}` : ""}`);
      }
    });
  });

  client.on("message", async (topic, message) => {
    if (topic === mqtt_topic) {
      try {
        const payload = JSON.parse(message.toString());

        const data = await database.addMeasurementData(payload);

        socket.broadcastMeasurementData(data);
      } catch (err) {
        console.error("MQTT Error -", err.message);
      }
    }
  });

  return client;
};
