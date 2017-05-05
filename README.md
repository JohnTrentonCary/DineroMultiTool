# DineroMultiConfigsTool
This is a tool for those who use dinero to run benchmarks against various CPU architectures. The tool is meant to help simplify the process of running a large amount of different configurations.

## Compilation Requirements
* If compiling using g++, g++ 5+ is required. This is due to g++ 4.8 not having a full implementation of the C++11 standard library "libstdc++", part of which includes regex. Using g++ 4.8 or earlier will result in a bug with processing the files into a single file for each benchmark

## Configuration Commands

Note: For any of the arguments, you can add a "P" before the ":" if you wish to use exponents instead of the value of 2 raised to those exponents.

#### Arguments Specific to this Program
| Name | Config File Arguments |
| --- | --- |
| Location of Dinero | DineroLocation: path |
| List of Benchmarks | Benchmarks: mark1.txt /home/desktop/mark2.txt... |
| The maximum number of threads allowed | ThreadLimit: 32 |

Note: The default for ThreadLimit is whatever OpenMP calculates as the safe number of threads to run. Additionally, only the first number of this argument will be read. The others will be ignored and thrown out

#### L1 Instruction and Data Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L1 Instruction Size | L1ISize: 8 32:128 512... | -l1-isize |
| L1 Instruction Block Size | L1IBSize: 8 32:128 512... | -l1-ibsize |
| L1 Instruction Sub Block Size | L1ISBSize: 8 32:128 512... | -l1-isbsize |
| L1 Instruction Associativity | L1IAssoc: nums | -l1-iassoc |
| L1 Data Size | L1DSize: 8 32:128 512... | -l1-dsize |
| L1 Data Block Size | L1DBSize: 8 32:128 512... | -l1-dbsize |
| L1 Data Sub Block Size | L1DSBSize: 8 32:128 512... | -l1-dsbsize |
| L1 Data Associativity | L1DAssoc: nums | -l1-dassoc |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L2 Unified Size | L2Size: 8 32:128 512... | -l2-usize |
| L2 Unified Block Size | L2BSize: 8 32:128 512... | -l2-ubsize |
| L2 Unified Sub Block Size | L2SBSize: 8 32:128 512... | -l2-usbsize |
| L2 Unified Associativity | L2Assoc: nums | -l2-uassoc |
| L2 Unified Associativity Hit Cost | L2AssocHit: nums | N/A |
| L2 Unified Associativity Miss Penalty | L2Miss: nums | N/A |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L3 Unified Size | L3Size: 8 32:128 512... | -l3-usize |
| L3 Unified Block Size | L3BSize: 8 32:128 512... | -l3-ubsize |
| L3 Unified Sub Block Size | L3SBSize: 8 32:128 512... | -l3-usbsize |
| L3 Unified Associativity | L3Assoc: nums | -l3-uassoc |
| L3 Unified Associativity Hit Cost | L3AssocHit: nums | N/A |
| L3 Unified Associativity Miss Penalty | L3Miss: nums | N/A |
