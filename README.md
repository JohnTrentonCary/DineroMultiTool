# DineroMultiConfigsTool
This is a tool for those who use dinero to run benchmarks against various CPU architectures. The tool is meant to help simplify the process of running a large amount of different configurations.

## Configuration Commands

Note: For any of the arguments, you can add a "P" before the ":" if you wish to use exponents instead of the value of 2 raised to those exponents. 

#### L1 Instruction and Data Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L1 Instruction Size | L1ISize: nums | -l1-isize |
| L1 Instruction Block Size | L1IBSize: nums | -l1-ibsize |
| L1 Instruction Sub Block Size | L1ISBSize: nums | -l1-isbsize |
| L1 Instruction Associtivity | L1IAssoc: nums | -l1-iassoc |
| L1 Data Size | L1DSize: nums | -l1-dsize |
| L1 Data Block Size | L1DBSize: nums | -l1-dbsize |
| L1 Data Sub Block Size | L1DSBSize: nums | -l1-dsbsize |
| L1 Data Associtivity | L1DAssoc: nums | -l1-dassoc |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L2 Unified Size | L2Size: nums | -l2-usize |
| L2 Unified Block Size | L2BSize: nums | -l2-ubsize |
| L2 Unified Sub Block Size | L2SBSize: nums | -l2-usbsize |
| L2 Unified Associtivity | L2Assoc: nums | -l2-uassoc |
| L2 Unified Associtivity Hit Cost | L2AssocHit: nums | N/A |
| L2 Unified Associtivity Miss Penalty | L2Miss: nums | N/A |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L3 Unified Size | L3Size: nums | -l3-usize |
| L3 Unified Block Size | L3BSize: nums | -l3-ubsize |
| L3 Unified Sub Block Size | L3SBSize: nums | -l3-usbsize |
| L3 Unified Associtivity | L3Assoc: nums | -l3-uassoc |
| L3 Unified Associtivity Hit Cost | L3AssocHit: nums | N/A |
| L3 Unified Associtivity Miss Penalty | L3Miss: nums | N/A |
