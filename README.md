MODULE SUMMARY

       Module                           code    ro data   rw data
       ------                           ----    -------   -------
    .\
       main.obj                         56      0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           56      0         0      
                                                                 
    .\FreeRTOS-Kernel\src\
       tasks.obj                        3770    8         300    
       queue.obj                        1692    0         0      
       list.obj                         184     0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           5646    8         300    
                                                                 
    .\FreeRTOS-Kernel\src\portable\CCS\MSP430X\
       portext.obj                      180     0         0      
       port.obj                         48      2         2      
    +--+--------------------------------+-------+---------+---------+
       Total:                           228     2         2      
                                                                 
    .\FreeRTOS-Kernel\src\portable\MemMang\
       heap_4.obj                       620     0         3086   
    +--+--------------------------------+-------+---------+---------+
       Total:                           620     0         3086   
                                                                 
    .\components\AHT20_component\
       AHT20_component.obj              522     4         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           522     4         0      
                                                                 
    .\components\AHT20_component\AHT20_conversions\
       AHT20_fastint_conversion.obj     36      0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           36      0         0      
                                                                 
    .\components\BMP280_component\
       BMP280_component.obj             676     0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           676     0         0      
                                                                 
    .\components\BMP280_component\BMP280_conversions\
       BMP280_linear_regression.obj     200     0         4      
    +--+--------------------------------+-------+---------+---------+
       Total:                           200     0         4      
                                                                 
    .\components\I2C_component\
       I2C_component.obj                200     0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           200     0         0      
                                                                 
    .\components\NEO6M_module\
       NEO6M_module.obj                 426     8         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           426     8         0      
                                                                 
    .\components\UART_component\
       uart_component.obj               306     0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           306     0         0      
                                                                 
    .\driverlib\MSP430FR2xx_4xx\
       gpio.obj                         30      28        0      
       wdt_a.obj                        22      0         0      
       pmm.obj                          6       0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           58      28        0      
                                                                 
    .\drivers\CLOCK_driver\
       clocks.obj                       284     0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           284     0         0      
                                                                 
    .\drivers\I2C_driver\
       i2c.obj                          512     2         52     
    +--+--------------------------------+-------+---------+---------+
       Total:                           512     2         52     
                                                                 
    .\drivers\SPI_driver\
       spi.obj                          194     2         14     
    +--+--------------------------------+-------+---------+---------+
       Total:                           194     2         14     
                                                                 
    .\drivers\UART_driver\
       uart.obj                         184     2         104    
    +--+--------------------------------+-------+---------+---------+
       Total:                           184     2         104    
                                                                 
    .\include\
       string_utils.obj                 426     0         2      
    +--+--------------------------------+-------+---------+---------+
       Total:                           426     0         2      
                                                                 
    .\interfaces\
       instantiator.obj                 62      0         166    
    +--+--------------------------------+-------+---------+---------+
       Total:                           62      0         166    
                                                                 
    .\os\
       freeRTOS_support.obj             38      0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           38      0         0      
                                                                 
    .\tasks\
       tasks.obj                        120     8         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           120     8         0      
                                                                 
    .\tasks\Common\Packet_buffers\GPS\
       gps_packet_buffer.obj            0       0         26     
    +--+--------------------------------+-------+---------+---------+
       Total:                           0       0         26     
                                                                 
    .\tasks\Common\Packet_buffers\Housekeeping\
       housekeeping_packet_buffer.obj   0       0         12     
    +--+--------------------------------+-------+---------+---------+
       Total:                           0       0         12     
                                                                 
    .\tasks\Info_status_gathering\
       HK_task.obj                      240     0         0      
       GPS_task.obj                     132     0         0      
    +--+--------------------------------+-------+---------+---------+
       Total:                           372     0         0      
       Grand Total:                     12050