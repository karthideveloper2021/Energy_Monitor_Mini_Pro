import 'package:flutter/material.dart';

class DevicePage extends StatefulWidget {
  const DevicePage({super.key});

  @override
  State<DevicePage> createState() => _DevicePageState();
}

class _DevicePageState extends State<DevicePage> {
  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size;
    return Scaffold(
      body: SafeArea(
        child: Container(
          padding: EdgeInsets.symmetric(horizontal: size.width / 20),
          child: Column(
            children: [
              SizedBox(height: size.height / 20),
              customText("Voltage (V)"),
              SizedBox(height: size.height / 20),
              customText("Current (A)"),
              SizedBox(height: size.height / 20),
              customText("Power (W)"),
            ],
          ),
        ),
      ),
    );
  }

  Widget customText(String text) {
    return Text(
      text,
      style: TextStyle(
        fontSize: 20,
        fontWeight: FontWeight.w600,
      ),
    );
  }
}
