let _db_mock = [];

export const getUniqueDeviceData = async () => {
  const dataDevice = _db_mock.map((e) => e["device"]);
  const dataDeviceUnique = new Set(dataDevice);

  return [...dataDeviceUnique];
};

export const getMeasurementData = async (device) => {
  if (device) {
    return _db_mock.filter((e) => e["device"] === device);
  }

  return _db_mock;
};

export const addMeasurementData = async (payload) => {
  const data = { received_at: new Date(), ...payload };

  _db_mock.push(data);

  console.log(data);
};
