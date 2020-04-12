#include <math.h>
#include <uWS/uWS.h>

#include <iostream>
#include <string>

#include "PID.hpp"
#include "json.hpp"

namespace {
// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
[[maybe_unused]] [[nodiscard]] constexpr double pi() { return M_PI; }
[[maybe_unused]] [[nodiscard]] constexpr double deg2rad(double x) {
  return x * pi() / 180;
}
[[maybe_unused]] [[nodiscard]] constexpr double rad2deg(double x) {
  return x * 180 / pi();
}

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
[[nodiscard]] string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  } else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}
}  // namespace

int main() {
  // for convenience
  using nlohmann::json;
  using std::string;

  uWS::Hub h;

  PID pid_steer(0.15, 0, -3);
  PID pid_throttle(-0.5, 0, 0);

  h.onMessage([&pid_steer, &pid_throttle](uWS::WebSocket<uWS::SERVER> ws,
                                          char *data, size_t length,
                                          uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);
        auto event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          auto cte = std::stod(j[1]["cte"].get<string>());
          auto speed = std::stod(j[1]["speed"].get<string>());
          auto angle = std::stod(j[1]["steering_angle"].get<string>());

          constexpr double max_speed = 70;
          double speed_target = max_speed;
          auto abs_angle = fabs(angle);
          if (abs_angle > 5)
            speed_target = max_speed - 40;
          else if (abs_angle > 4)
            speed_target = max_speed - 30;
          else if (abs_angle > 3)
            speed_target = max_speed - 20;
          else if (abs_angle > 2)
            speed_target = max_speed - 10;
          else
            speed_target = max_speed;

          auto speed_e = speed - speed_target;

          /**
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          pid_steer.UpdateError(cte);
          auto steer_value = pid_steer.TotalError();
          /* Steering value is [-1, 1] */
          steer_value =
              (steer_value > 1) ? 1 : ((steer_value < -1) ? -1 : steer_value);

          pid_throttle.UpdateError(speed_e);
          auto throttle_value = pid_throttle.TotalError();

          // DEBUG
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value
                    << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value;  // 0.3;
          string msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  });  // end h.onMessage

  h.onConnection([](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([](uWS::WebSocket<uWS::SERVER> ws, int code, char *message,
                       size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }

  h.run();
}