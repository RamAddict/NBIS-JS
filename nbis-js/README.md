# **NBIS-JS**

Web assembly transpilation of some functions from the old NIST-NBIS project. Currently the functions we implemented are finger Matching, with Mindtct and Bozorth, and NFIQ 1.0 score.

### At the moment this project only runs in the browser.

## **Usage**

```js
import {
    checkDuplicateFingerFromBase64,
    getNfiqScoreFromBase64,
} from "./nbis-js.js";

await checkDuplicateFingerFromBase64(
    "fingerWsqInBase64",
    "otherFingerWsqInBase64"
);

await getNfiqScoreFromBase64("fingerWsqInBase64");
```
