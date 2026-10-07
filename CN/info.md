# CRC

Basic CRC code using XOR division.

### Changes for different CRCs

| CRC       | Generator           |              Zeros | CRC bits |
| --------- | ------------------- | -----------------: | -------: |
| Basic     | `10011`             |             `0000` |        4 |
| CRC-8     | `100000111`         |         `00000000` |        8 |
| CRC-12    | `1000001010011`     |     `000000000000` |       12 |
| CRC-16    | `11000000000000101` | `0000000000000000` |       16 |
| CRC-CCITT | `10001000000100001` | `0000000000000000` |       16 |

### In the code, change only these 3 lines:

```cpp
string generator = "10011";

string temp = data + "0000";

string crc = temp.substr(temp.length() - 4);
```

For each CRC, replace them with the corresponding **Generator, Zeros, and CRC bits** from the table.
