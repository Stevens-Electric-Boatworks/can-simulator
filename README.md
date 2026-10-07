# can-simulator
Internal tool to simulate realistic CAN bus activity for TidalCore.

## DCFGen

To generate the `master.dcf` file, download dcfgen using the Lely documentation, and then run the following command:

```bash
 dcfgen --no-strict -r -d dcfgen_out master.yml
```

A sample of the current ones are provided in this repo. 
