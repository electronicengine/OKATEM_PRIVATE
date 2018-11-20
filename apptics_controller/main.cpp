
#include "controller.h"
#include "videostream.h"
#include "datatypes.h"





int main()
{


    VideoStream stream;
    std::string ip_address;

    int controller_port = 24000;
    int stream_port = 25000;

    int character;

    std::cout << "Enter Ip address to connect" << std::endl;
    std::cin >> ip_address;
    std::cout << "Enter stream port" << std::endl;
    std::cin >> stream_port;


    Controller controller(ip_address, controller_port);

    stream.start(ip_address, stream_port);



    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);


    while (true)
    {

        character = (int)getch();

            switch (character)
            {
                case 'w':
                    controller.turnUp();

                    break;
                case 'a':
                    controller.turnRight();

                    break;
                case 's':
                    controller.turnDown();

                    break;
                case 'd':
                    controller.turnLeft();
                    break;

                case 'z':
                    controller.servo1Backward();

                    break;

                case 'x':
                    controller.servo1Forward();

                    break;

                case 'c':
                    controller.servo2Backward();

                    break;

                case 'v':
                    controller.servo2Forward();


                    break;
                case 'e':
                    controller.increaseSpeed();

                    break;

                case 'q':
                    controller.decreaseSpeed();

                    break;

            case 'p':
                    controller.updateFirmware();

                break;

            default:
                    break;
            }


        napms(1);

    }

    return 0;
}




