# SiSensorsMeasUtilities
Utilities scripts for Si sensors measurments.

To produce plots use the following procedure:

1) Place your measurments in Data/<some_dir>
2) Convert .txt files to .root files that contain TGraphs:
```bash
sh txt2root.sh <some_dir> <meas_date>
```
For example:
```bash
sh txt2root.sh Halfmoon_outter_tracker_6inch_VPX28441_WNo3_1003_chipNo17 20200207
```
Hint: ```<meas_date>``` can be any unique identifying string.

3) Process the measurements and produce individual plots:
```bash
root -l subtractStrayCapacitance.C\(<signal_file>,<background_file>,<isMOS>\)
```
where ```isMOS``` variable should be set to 1 for MOS measurements. For example:
```bash
root -l subtractStrayCapacitance.C\(\"root/Halfmoon_upper_right_300um_Z3415_WNo6/MOS_2000_CV_1kHz_20200204.root\",\"root/Halfmoon_upper_right_300um_Z3415_WNo6/SetupCapacitance_step0p25V_CV_1kHz_20200204.root\",1\)
```
To process many at once:
```bash
for i in 1 10 100 1000;
do
root -l -q subtractStrayCapacitance.C\(\"root/Halfmoon_upper_right_300um_Z3415_WNo6/MOS_2000_CV_${i}kHz_20200204.root\",\"root/Halfmoon_upper_right_300um_Z3415_WNo6/SetupCapacitance_step0p25V_CV_${i}kHz_20200204.root\",1\);
done
```

4) Then use the ```multigraph.C``` script to produce collective graphs.
