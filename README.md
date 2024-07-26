# libzhl

The ZHL Bühlmann algorithm is a decompression model employs theoretical tissue compartments and gas exchange dynamics to calculate safe ascent profiles, accommodating various gas mixtures as the ambient pressure changes.

<p align="center">
  <img src="https://github.com/user-attachments/assets/c48b1abd-a247-4a28-9be8-d7285a8e1ba7" />
</p>


## Optimal gas mixture

The model is based on the Dalton's Law in combination with Partial Pressures **constraint optimisation**  on the pressure limits recommended in the **US Navy Diving Manual (Revision 7, 2020)**:

- PP02 (21,278 Pa - 141,855 Pa) - to eliminate O2 toxicity under high ambient pressure.
- PPN2 (0 Pa - 354,638 Pa) - to amortise N2 narcotic effect under high ambient pressure.

**WARNING:**
Underlying model assumes no hazardous properties of Helium under high ambient pressures:
- PPHe (0 Pa, ∞ Pa)

```bash
./mixture --min=1 --max=10 --interval=0.5 --pressure-unit=ata
```

| Ambient Pressure  | PP02 (ATA) | VO2      | PPN2 (ATA) | VN2      | PPHe (ATA) | VHe       | 
| ----------------- | ---------- | -------- | ---------- | -------- | ---------- | --------- |
| 1 ATA             | 0.209998   | 0.209998 | 0.790002   | 0.790002 | 0          | 0         |
| 1.5 ATA           | 0.314996   | 0.209998 | 1.185      | 0.790002 | 0          | 0         |
| 2 ATA             | 0.419995   | 0.209998 | 1.58       | 0.790002 | 0          | 0         |
| 2.5 ATA           | 0.524994   | 0.209998 | 1.97501    | 0.790002 | 0          | 0         |
| 3 ATA             | 0.629993   | 0.209998 | 2.37001    | 0.790002 | 0          | 0         |
| 3.5 ATA           | 0.734991   | 0.209998 | 2.76501    | 0.790002 | 0          | 0         |
| 4 ATA             | 0.83999    | 0.209998 | 3.16001    | 0.790002 | 0          | 0         |
| 4.5 ATA           | 0.944989   | 0.209998 | 3.5        | 0.777779 | 0.0550062  | 0.0122236 |
| 5 ATA             | 1.04999    | 0.209998 | 3.5        | 0.700001 | 0.450007   | 0.0900015 |
| 5.5 ATA           | 1.15499    | 0.209998 | 3.5        | 0.636365 | 0.845009   | 0.153638  |
| 6 ATA             | 1.25999    | 0.209998 | 3.5        | 0.583334 | 1.24001    | 0.206668  |
| 6.5 ATA           | 1.36498    | 0.209998 | 3.5        | 0.538462 | 1.63501    | 0.25154   |
| 7 ATA             | 1.4        | 0.2      | 3.5        | 0.500001 | 2.1        | 0.299999  |
| 7.5 ATA           | 1.4        | 0.186667 | 3.5        | 0.466667 | 2.6        | 0.346666  |
| 8 ATA             | 1.4        | 0.175    | 3.5        | 0.437501 | 3.1        | 0.387499  |
| 8.5 ATA           | 1.4        | 0.164706 | 3.5        | 0.411765 | 3.6        | 0.423529  |
| 9 ATA             | 1.4        | 0.155556 | 3.5        | 0.388889 | 4.1        | 0.455555  |
| 9.5 ATA           | 1.4        | 0.147368 | 3.5        | 0.368422 | 4.6        | 0.48421   |
| 10 ATA            | 1.4        | 0.14     | 3.5        | 0.35     | 5.1        | 0.51      |

# DISCLAIMER

**WARNING**: USE OF THIS LIBRARY FOR SCUBA/TECHNICAL DIVING MAY CAUSE HEALTH PROBLEMS OR DEATH

The use of this library for scuba/technical diving is strictly prohibited. The calculations and algorithms used in this library are not intended for use in life-critical applications, including scuba/technical diving.

## RISKS ASSOCIATED WITH SCUBA/TECHNICAL DIVING

Scuba/technical diving is a high-risk activity that can result in serious health problems or death. The use of this library for scuba/technical diving may increase the risk of:

- Decompression sickness (DCS)
- Nitrogen narcosis
- Oxygen toxicity
- Carbon dioxide poisoning
- Other diving-related injuries or illnesses

## LIMITATIONS OF THIS LIBRARY

This library is not designed to provide a safe or reliable means of calculating dive plans or managing gas mixtures for scuba/technical diving. The calculations and algorithms used in this library are based on simplified models and assumptions that may not accurately reflect the complexities of real-world diving scenarios.

## USER RESPONSIBILITY

By using this library, you acknowledge that you understand the risks associated with scuba/technical diving and that you are responsible for ensuring your own safety and the safety of others. You also acknowledge that you have read and understood the warnings and disclaimers provided in this document.

## NO WARRANTY OR LIABILITY

The authors and maintainers of this library disclaim any warranty or liability for damages or injuries resulting from the use of this library for scuba/technical diving. By using this library, you release and hold harmless the authors and maintainers of this library from any claims or liabilities arising from the use of this library.

## RECOMMENDATIONS

If you are a scuba/technical diver, we strongly recommend that you use a reputable and safety-tested dive planning software or consult with a qualified diving professional to ensure your safety and the safety of others.

## ACKNOWLEDGMENT

By using this library, you acknowledge that you have read and understood the warnings and disclaimers provided in this document and that you are aware of the risks associated with scuba/technical diving.
