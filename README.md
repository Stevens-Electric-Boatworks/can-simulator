# InMotion CAN Simulator
WIP tool to simulate realistic CAN bus activity for TidalCore.

## Configuring

To install the required dependencies:
```bash
sudo apt update
sudo apt install libglfw3-dev libgl1-mesa-dev xorg-dev
```


## DCFGen

To generate the `master.dcf` file, download dcfgen using the Lely documentation, and then run the following command:

```bash
 dcfgen --no-strict -r -d dcfgen_out master.yml
```

A sample of the current ones are provided in this repo. 
