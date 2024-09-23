
# Experiment: 01_gpio_hal

Linker summary:
```bash
Memory region         Used Size  Region Size  %age Used
         ITCMRAM:          32 B        16 KB      0.20%
           FLASH:        5264 B         2 MB      0.25%
         DTCMRAM:          0 GB       128 KB      0.00%
             RAM:         984 B       384 KB      0.25%
         BKPSRAM:          0 GB         4 KB      0.00%
```


```bash
 Symbol size per category
    IRQ related                  302 bytes
    GPIO related                 1058 bytes
    HAL related                 1929 bytes
    App related                  454 bytes
    CRT related                 1397 bytes
```

Where:
 - HAL excludes GPIO related functions


# Experiment: 02_gpio_ll

Linker summary:
```bash
Memory region         Used Size  Region Size  %age Used
         ITCMRAM:          32 B        16 KB      0.20%
           FLASH:        2180 B         2 MB      0.10%
         DTCMRAM:          0 GB       128 KB      0.00%
             RAM:         976 B       384 KB      0.25%
         BKPSRAM:          0 GB         4 KB      0.00%
```

Analysis:
```bash
  Symbol size per category
    IRQ related                  302 bytes
    GPIO related                  372 bytes
    HAL related                   72 bytes
    App related                  674 bytes
    CRT related                  693 bytes
```

Observations:
 - Total analysis: 2113 not equal to 2180, yet all symbols counted -> not taking padding and alignment into account.
 - GPIO does take up quite significant part for just one pin
   - This mainly boils down to the `LL_GPIO_Init` function, accounts for 372 bytes.
 - CRT takes up a lot of space, mostly related to `atexit` and related code which is not even used.
