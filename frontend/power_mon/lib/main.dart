import 'package:flutter/material.dart';
import 'package:power_mon/pages/device.dart';
import 'package:power_mon/pages/home.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(
          colorSchemeSeed: const Color(0xff6750a4), useMaterial3: true),
      home: HomePage(),
    );
  }
}
