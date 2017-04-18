# DineroMultiConfigsTool
This is a tool for those who use dinero to run benchmarks against various CPU architectures. The tool is meant to help simplify the process of running a large amount of different configurations.

## Configuration Commands

Legend
| Name | Meaning |
| --- | --- |
| nums| You can enter the values that you wish to be used here |
| [P] | You can add a P at the end of the argument to have the program treat your values as if they are powers of 2 |

#### L1 Instruction and Data Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L1 Instruction Size | L1ISize[P]: nums | -l1-isize |
| L1 Instruction Block Size | L1IBSize[P]: nums | -l1-ibsize |
| L1 Instruction Sub Block Size | L1ISBSize[P]: nums | -l1-isbsize |
| L1 Instruction Associtivity | L1IAssoc[P]: nums | -l1-iassoc |
| L1 Data Size | L1DSize[P]: nums | -l1-dsize |
| L1 Data Block Size | L1DBSize[P]: nums | -l1-dbsize |
| L1 Data Sub Block Size | L1DSBSize[P]: nums | -l1-dsbsize |
| L1 Data Associtivity | L1DAssoc[P]: nums | -l1-dassoc |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L2 Unified Size | L2Size[P]: nums | -l2-usize |
| L2 Unified Block Size | L2BSize[P]: nums | -l2-ubsize |
| L2 Unified Sub Block Size | L2SBSize[P]: nums | -l2-usbsize |
| L2 Unified Associtivity | L2Assoc[P]: nums | -l2-uassoc |
| L2 Unified Associtivity Hit Cost | L2AssocHit: nums | N/A |
| L2 Unified Associtivity Miss Penalty | L2Miss: nums | N/A |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L3 Unified Size | L3Size[P]: nums | -l3-usize |
| L3 Unified Block Size | L3BSize[P]: nums | -l3-ubsize |
| L3 Unified Sub Block Size | L3SBSize[P]: nums | -l3-usbsize |
| L3 Unified Associtivity | L3Assoc[P]: nums | -l3-uassoc |
| L3 Unified Associtivity Hit Cost | L3AssocHit: nums | N/A |
| L3 Unified Associtivity Miss Penalty | L3Miss: nums | N/A |
