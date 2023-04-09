import 'dart:convert';

import 'package:power_mon/models/device_model.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

class DeviceRespository {
  final _websocket_channel;

  DeviceRespository({required websocket_channel}):_websocket_channel=websocket_channel;

  Stream<DeviceDataModel> getDeviceData() async* {
    dynamic getNewData=_websocket_channel.stream;
    DeviceDataModel deviceData=DeviceDataModel.fromJson(jsonDecode(getNewData));
    yield* Stream.value(deviceData);
  }

}
