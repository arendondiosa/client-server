#include "lib/fs.hpp"
#include "lib/json.hpp"

using json = nlohmann::json;

int main() {
  cout << "This is the client\n";

  context ctx;
  socket s(ctx, socket_type::req);

  cout << "Connecting to tcp port 5555\n";
  s.connect("tcp://localhost:5555");
    system("mkdir downloads");

  string name, user, command, text;

  cout << "Enter the username:  ";
  cin >> user;
  cout << "WELCOME " + user << endl;
  cout << "Enter a comand" << endl;
  message m, response;

  while (true) {
    cout << ">> $  ";
    cin >> command;

    if (command == "add") {
      string test = getFile(name);
      while (true) {
        m << "add";
        s.send(m);
        s.receive(response);
        cin >> name;
        json file;

        if (checkFileExist(test)) {
          file["user"] = user;
          file["name"] = name;
          file["file"] = string_to_hex(test);
          //JSON to string, to tabs
          m << file.dump(2);
        } else m << "NO";

        s.send(m);
        //RESPONSE
        s.receive(response);
        response >> text;
        cout << text << endl;
      }
    } else if (command == "ls") {
      m << "ls";
      s.send(m);
      s.receive(response);
      cout << "getting" << endl;
      m << user;
      s.send(m);
      s.receive(response);
      response >> text;
      cout << user + " FILES:" << endl;
      cout << text << endl;
    } else if (command == "rm") {
      // cout << "rm" << endl;
      m << "rm";
      s.send(m);
      s.receive(response);
      response >> text;
      cout << text << endl;
      cin >> name;

      json get;
      get["user"] = user;
      get["file"] = name;
      m << get.dump(2);
      s.send(m);
      s.receive(response);
      response >> text;
      // cout << text << endl;
      if (text == "NO FILE")
        cout << "File no found in server !!!" << endl;
      else {
        cout << name << " was delete from server" << endl;
      }
    } else if (command == "get") {
      m << "get";
      s.send(m);
      s.receive(response);
      response >> text;
      cout << text << endl;
      cin >> name;

      json get;
      get["user"] = user;
      get["file"] = name;
      m << get.dump(2);
      s.send(m);
      s.receive(response);
      response >> text;
      // cout << text << endl;
      if (text == "NO FILE")
        cout << "File no found in server !!!" << endl;
      else {
        putFileClient(name, text);
      }
      // cout << user + " files:" << endl;
    } else if (command == "exit") {
      cout << "Closing " + user + " account" << endl;
      break;
    } else cout << "Enter a correct command" << endl;
  }
  // system("rm -r downloads/");
  return 0;
}
