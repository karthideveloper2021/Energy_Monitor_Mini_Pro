class DeviceModel {
  String? name;
  String? id;

  DeviceModel({required this.id, this.name});
}

class DeviceDataModel {
  late DeviceModel device;
  double? power;
  double? current;
  double? voltage;

  DeviceDataModel({required this.device});

  DeviceDataModel.fromJson(Map<String, dynamic> json) {
    device = DeviceModel(id: json["id"]);
    power = json["power"];
    voltage = json["voltage"];
    current = json["current"];
  }
}
