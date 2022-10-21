import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  static const platform = const MethodChannel('com.dev.app/channel_name');

  Future<Null> _managePower() async {
    try {
      final String result = await platform.invokeMethod('powerManage');
    } on PlatformException catch (e) {
      print(e);
    }
  }

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Demo gpos700x',
      home: Scaffold(
        body: Column(
          children: [
            SizedBox(height: 50),
            ElevatedButton(onPressed: _managePower,
                child: Text("Toast") ),
          ],
        ),
      ),

    );
  }
}
