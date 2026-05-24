import mysql from "mysql2/promise";

let _pool;

export const initDatabase = async () => {
  _pool = mysql.createPool({
    host: "localhost",
    port: 3306,
    user: "system",
    password: "supersecret_system",
    database: "iot_db",
    waitForConnections: true,
    connectionLimit: 10,
    queueLimit: 0,
  });

  _pool
    .getConnection()
    .then((conn) => {
      console.log("MySQL connection established");
      conn.release();
    })
    .catch((err) => {
      console.error(`CRITICAL - MySQL connection failed${err.message ? `:${err.message}` : ""}`);
      process.exit(1);
    });
};

export const getMeasurementData = async () => {
  const query = `SELECT * FROM measurements`;
  const [rows] = await _pool.execute(query);

  return rows;
};

export const addMeasurementData = async (payload) => {
  const data = { received_at: new Date(), ...payload };

  const query = `INSERT INTO measurements (device, sensor, payload, received_at) VALUES (?, ?, ?, ?)`;
  await _pool.execute(query, [data.device, data.sensor, data.payload, data.received_at]);

  console.log(data);

  return data;
};
