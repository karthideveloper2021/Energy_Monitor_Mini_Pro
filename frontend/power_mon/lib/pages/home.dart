import 'package:flutter/material.dart';
import 'package:power_mon/pages/device.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  List devices = ["Fan", "Light", "Lamp"];

  @override
  Widget build(BuildContext context) {
    Size size = MediaQuery.of(context).size;
    return Scaffold(
      floatingActionButton: FloatingActionButton(
        onPressed: _showAddDevicePopup,
        child: Icon(Icons.add),
        backgroundColor: Color.fromARGB(255, 237, 4, 94),
      ),
      body: SafeArea(
          child: GridView.builder(
        gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
          mainAxisSpacing: size.height / 90,
          crossAxisSpacing: size.width / 90,
          crossAxisCount: 2,
        ),
        itemCount: devices.length,
        itemBuilder: (_, index) {
          return Card(
            color: Color.fromARGB(255, 50, 164, 234),
            margin: EdgeInsets.all(size.width / 45),
            child: InkWell(
              onTap: () => Navigator.push(context,
                  MaterialPageRoute(builder: (context) => DevicePage())),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  SizedBox(height: size.height / 50),
                  Align(
                    alignment: Alignment.centerRight,
                    child: Container(
                      decoration: BoxDecoration(
                          boxShadow: [
                            BoxShadow(
                              blurRadius: 0.8,
                              spreadRadius: 2,
                              color: Colors.white,
                            )
                          ],
                          borderRadius: BorderRadius.circular(10),
                          color: Color.fromARGB(255, 255, 20, 4)),
                      height: size.height / 60,
                      width: size.height / 60,
                      margin: EdgeInsets.symmetric(horizontal: size.width / 70),
                    ),
                  ),
                  SizedBox(height: size.height / 15),
                  Text(
                    devices[index],
                    style: TextStyle(
                      color: Colors.white,
                      fontWeight: FontWeight.bold,
                      fontSize: 20.0,
                    ),
                  ),
                ],
              ),
            ),
            elevation: 6,
          );
        },
      )),
    );
  }

  Future<void> _showAddDevicePopup() async {
    return showDialog(
        context: context,
        builder: (context) {
          return AlertDialog(
            title: Text("Add New Device"),
            content: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                TextFormField(
                  decoration: InputDecoration(
                    labelText: "Device Name",
                  ),
                ),
                TextFormField(
                  decoration: InputDecoration(
                    labelText: "Device Id",
                  ),
                )
              ],
            ),
            actions: [
              TextButton(onPressed: () {}, child: Text("Add")),
              TextButton(
                onPressed: () {},
                child: Text("Cancel"),
              )
            ],
          );
        });
  }
}
