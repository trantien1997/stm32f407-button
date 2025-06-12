
# ✅ Test Environment & Command Notes

---

## 🛑 Pause & Release BS Setup

```bash
# Pause setup
/home/paltest/resbro/rq -q <bs_name> -p

# Release setup
/home/paltest/resbro/rq -q <bs_name> -r
```

### List of BS to test:
- `aravalli_bs`
- `medora_bs`
- `shasta_n_bs`
- `kailash_bs`
- `yukon_bs`  _(with reason: "Run manual test")_
- `whitney_bs`
- `nandi_bs`
- `shasta_bs`
- `vindhya_bs`

---

## 🖥️ Run Simulator

### SSH into simulator:
```bash
ssh falcon -X
```

### Start simulator:
```bash
cdsim
```

### Run simulator with official image:
```bash
./sim.py -t ../../../pal/schema/services.schema -o OS_7_X_X_9053_R01/ -f "OS6870"
```

### Run simulator with private image:
```bash
./sim.py -t ../../../pal/schema/services.schema -f "OS9900"
```

> **Available platform image options:**
> `OS6560`, `OS9900`, `OS6465`, `OS9912`, `OS6570`, `OS6870`

---

## 📦 Build Package

### Build for a specific platform:
```bash
time make clean -j24 PLATFORM=armv7_helix4 V=1
time make -s -j24 PLATFORM=armv7_helix4 V=1 php
```

### Clean after building:
```bash
rm -rf built/ tps/objs/ tps/built/ tps/installed/
```

---

## 🗂️ Platform & Board Mapping

| Platform     | Boards                              |
|--------------|--------------------------------------|
| I686         | medora, yukon, shasta_n, kailash     |
| ARM_H4       | shasta                               |
| ARM_MV38X    | nandi                                |
| ARM_AC3      | aravalli, nandi                      |
| ARM_AC5X     | whitney, dronagiri                   |
| X86_64       | medora                               |
| X86_64_OCP   | yukon, shasta_n, kailash             |

---

## 🔢 Image Build Information

### Get official image:
```bash
cat numbers/official_build_num
# /images/aos_images/bop/OS_7_X_X_9287_R01/nandi/Release
```

---

## 🧪 Test Checklist

**Minimum platforms required for testing new packages:**
- medora
- shasta
- nandi
- whitney
- yukon

---

## 🔍 Other Useful Commands

### Check if switch is SLAVE or MASTER:
```bash
show virtual top
```

### Disable SSL before curl test:
```bash
webview force-ssl disable
```

### Enable webview:
```bash
webview server enable
webview access enable
```

### Add macro when pkg includes ALE's code change:
```c
/* BEGIN ALU_ADDS_CHANGES */
// ...
/* END ALU_ADDS_CHANGES */

#ifdef ALU_ADDS_CHANGES
// ...
#endif /* ALU_ADDS_CHANGES */
```

### Apply a patch file:
```bash
patch -p1 < Patch_file/patchfile.patch
```

---

## 📁 Perforce Commands

### Remove shelved changelist:
```bash
p4 shelve -c <id> -d
```

### Delete changelist:
```bash
p4 change -d <id>
```

### Rename folder:
```bash
p4 edit bluez-4.101/...
p4 move bluez-4.101/... bluez/...
```
