# DineroMultiTool
DineroMultiTool was built to automate the generation, execution, and analysis across large batches of configurations and benchmarks on a Dinero IV Cache Simulator.

More specifically, it is a tool for those who use Dinero IV to run benchmarks against various CPU cache architectures. The tool is meant to simplify the process of running a large amount of different cache configurations. DineroMultiTool provides configuration generation, execution automation, and CPI analysis of all valid configurations executed. All invalid configurations are filtered out.

## How to use
To use DineroMultiTool you must
 1. Write/edit an input file that contains all the arguements that define what configurations you wish to run. Please refer to sections below for guidence 
 2. Execute DineroMultiTool and hand it your input file as the 2nd command line arguement. For example: "./DineroMultiTool test.dinconfig"
 3. Go do whatever you would like to do which the program generates every possible valid configuration, executes execute these configurations for every defined benchmark and then analyzes the results of the simulations.
 4. Once DineroMultiTool has finished, the data for every run will be stored within a folder that has the same name as the benchmark that was used. Additionally, a folder called "Combined" will be produced which contains all of the data from every simulation for each benchmark consolidated into 1 file for each benchmark

## Compilation Requirements
* If compiling using g++, g++ 5 or sooner is required to prevent a bug within the earlier versions of g++.

## Rules and Tips for Writing/Using the input file
* For every cache level you wish to run configurations for (L1 Instruction, L1 Data, L2, L3) you must include that cache's:
  * Size
  * Block Size
  * Sub Block Size
  * Associativity 

* Associativity hit and missPenalty are optional however, CPI will not be calculated without them
 
* For every set of numbers you wish to use as a range (12 through 15) you must include a colon between the 2 numbers with no spaces. 
for example: 12:15

* For any of the arguments, you can add a "P" before the ":" if you wish to use exponents instead of the value of 2 raised to those exponents.

* Ranges and non-exponential numbers, currently, should not be combined. With the current implementation DineroMultiTool will interprent 32:64 as you wanting the values 32, 33, 34, 35...64. This will most likely be fixed in future iterations. 

* The default for ThreadLimit is whatever OpenMP calculates as the safe number of threads to run. Additionally, only the first number of this argument will be read. The others will be ignored and thrown out

## Configuration Commands

#### Arguments Specific to this Program
| Name | Config File Arguments |
| --- | --- |
| Location of Dinero | DineroLocation: path |
| List of Benchmarks | Benchmarks: mark1.txt /home/desktop/mark2.txt... |
| The maximum number of threads allowed | ThreadLimit: Dependent upon # of logical threads on system |

#### L1 Instruction Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L1 Instruction Size | L1InstSize: 8 32:128 512... | -l1-isize |
| L1 Instruction Block Size | L1InstBlockSize: 8 32:128 512... | -l1-ibsize |
| L1 Instruction Sub Block Size | L1InstSubBlockSize: 8 32:128 512... | -l1-isbsize |
| L1 Instruction Associativity | L1InstAssoc: nums (Positive Integers Only) | -l1-iassoc |
| L1 Instruction Associativity Hit Cost (in cycles) | L1InstAssocHit: nums (Positive Integers Only) | N/A |
| L1 Instruction Associativity Miss Penalty (in cycles) | L1InstAssocMiss: nums (Positive Integers Only) | N/A |

#### L1 Data Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L1 Data Size | L1DataSize: 8 32:128 512... | -l1-dsize |
| L1 Data Block Size | L1DataBlockSize: 8 32:128 512... | -l1-dbsize |
| L1 Data Sub Block Size | L1DataSubBlockSize: 8 32:128 512... | -l1-dsbsize |
| L1 Data Associativity | L1DataAssoc: nums (Positive Integers Only) | -l1-dassoc |
| L1 Data Associativity Hit Cost (in cycles) | L1DataAssocHit: nums (Positive Integers Only) | N/A |
| L1 Data Associativity Miss Penalty (in cycles) | L1DataAssocMiss: nums (Positive Integers Only) | N/A |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L2 Unified Size | L2Size: 8 32:128 512... | -l2-usize |
| L2 Unified Block Size | L2BlockSize: 8 32:128 512... | -l2-ubsize |
| L2 Unified Sub Block Size | L2SubBlockSize: 8 32:128 512... | -l2-usbsize |
| L2 Unified Associativity | L2Assoc: nums (Positive Integers Only) | -l2-uassoc |
| L2 Unified Associativity Hit Cost (in cycles) | L2AssocHit: nums (Positive Integers Only) | N/A |
| L2 Unified Associativity Miss Penalty (in cycles) | L2AssocMiss: nums (Positive Integers Only) | N/A |

#### L2 Unified Caches
| Name | Config File Argument | Equivalent Dinero Argument |
| --- | --- | --- |
| L3 Unified Size | L3Size: 8 32:128 512... | -l3-usize |
| L3 Unified Block Size | L3BlockSize: 8 32:128 512... | -l3-ubsize |
| L3 Unified Sub Block Size | L3SubBlockSize: 8 32:128 512... | -l3-usbsize |
| L3 Unified Associativity | L3Assoc: nums (Positive Integers Only) | -l3-uassoc |
| L3 Unified Associativity Hit Cost (in cycles) | L3AssocHit: nums (Positive Integers Only) | N/A |
| L3 Unified Associativity Miss Penalty (in cycles) | L3AssocMiss: nums (Positive Integers Only) | N/A |


## Glossary of Terms
| Term | Description |
| --- | --- |
| Associativity | The division of direct-mapped cache into separate cache sets in an attempt to reduce the amount of misses to cache |
| Cache Block | The fundamental unit of storage in cache memory. |
| Cache Sub-Block | Sections within a cache block that share one cache tag. |
| Cycles per Instruction (CPI) | The average # of clock cycles that a system takes to execute an instruction for a program. |
| Hit Cost | Amount of CPU cycles used in the event of a cache hit. |
| Miss Penalty | Amount of CPU cycles used in the event of a cache miss. |

