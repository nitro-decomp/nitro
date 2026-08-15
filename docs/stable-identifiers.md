# Stable identifiers
It's not always easy to name functions that have just been decompiled, so we use a stable identifier system to act as a placeholder name until the function can be documented. We chose this system because `dsd`'s default naming i.e. `func_{address}` is not stable across different games.

Functions are categorised by module, then identified by a unique four digit ID. The function identifiers take the form `{module}_func_{id}`, for example `OS_func_0175`.

The next available ID increases whenever a new ID is used, so refer to the table below for the next available identifier in each SDK module. Please update the table as you use a new identifier.

| Module | Next identifier  |
| ------ | ---------------- |
| `CARD` | `CARD_func_0093` |
| `FS`   |   `FS_func_0102` |
| `FX`   |   `FX_func_0003` |
| `G2`   |   `G2_func_0007` |
| `G3`   |   `G3_func_0001` |
| `GX`   |   `GX_func_0012` |
| `MB`   |   `MB_func_0089` |
| `MI`   |   `MI_func_0021` |
| `OS`   |   `OS_func_0179` |
| `PM`   |   `PM_func_0051` |
| `RTC`  |  `RTC_func_0014` |
| `SND`  |  `SND_func_0056` |
| `TP`   |   `TP_func_0008` |
| `WM`   |   `WM_func_0040` |
