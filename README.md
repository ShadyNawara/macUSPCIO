# macUSPCIO
This driver (kext) is built using IOKit to allow communication between a user space application and the IO Space of a PCI Device.
The driver is intended as an aid in writing other drivers in user space first where it is easier to debug and test before converting to kernel space.
Apple's new DriverKit provides similar benefits but does not yet expose all functionalities available in IOKit.

The driver can be configured to match with any pci device specified in the info.plist -> IOKitPersonalities -> macUSPCIO -> IOPCIClassMatch (or any other matching property)

see: [https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/Matching/Matching.html](https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/Matching/Matching.html) for more info on driver matching.

### Current code and release build are set to match with IOPCIClass 0c050000 for matching with smbus class controllers

## Installation
### Method 1 - OpenCore
- Add driver to OC/Kexts
- Add the following driver entry to your config.plist under Kernal->Add or use the snapshot function (Cmd+R) in [ProperTree](https://github.com/corpnewt/ProperTree)

```
	<dict>
		<key>BundlePath</key>
		<string>macUSPCIO.kext</string>
		<key>Comment</key>
		<string>macUSPCIO.kext</string>
		<key>Enabled</key>
		<true/>
		<key>ExecutablePath</key>
		<string>Contents/MacOS/macUSPCIO</string>
		<key>Arch</key>
		<string>Any</string>
		<key>MaxKernel</key>
		<string></string>
		<key>MinKernel</key>
		<string></string>
		<key>PlistPath</key>
		<string>Contents/Info.plist</string>
	</dict>
```
### Method 2 - Manual (not Recommended)
- SIP must be disabled (or at least the driver signing feature)
- set .kext ownership to 0:0 (`sudo chown -R 0:0 ./macUSPCIO.kext`)
- run `sudo kextload ./macUSPCIO.kext`

### Supports macOS 10.15+

## Security Concern
This driver exposes internal pci devices to free user space access. This may pose a security risk so use with caution. 
I am not responsible if you brick your device.

## References
With the release of Apple's new DriverKit, information on writing IOKit drivers is extremely sparse and outdated. The following resources were very helpful
- [Apple's Sample PCI Driver](https://github.com/apple-oss-distributions/IOPCIFamily/tree/IOPCIFamily-484.60.4/AppleSamplePCI)
- [Xerub Kexty, Simple User Client Implementation Sample](https://github.com/xerub/kexty/tree/master/kext)
- [VoodooSMBus, mac kernel driver for the Intel I801 controller](https://github.com/VoodooSMBus/VoodooSMBus)
- [OS X and iOS Kernel Programming - PCI in I/O Kit eBook, General info on writing PCI IOKit Drivers](https://ebookreading.net/view/book/EB9781430235361_56.html)
