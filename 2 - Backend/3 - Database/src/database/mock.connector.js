let _db_mock = [];

export const getMeasurementData = async () => {

  return _db_mock;
};

export const addMeasurementData = async (payload) => {
  const data = { received_at: new Date(), ...payload };

  _db_mock.push(data);

  console.log(data);
};
