Bootstrap: docker
From: ubuntu

%setup
     ## The "%setup"-part of this script is called to bootstrap an empty
     ## container. It copies the source files from the branch of your
     ## repository where this file is located into the container to the
     ## directory "/planner". Do not change this part unless you know
     ## what you are doing and you are certain that you have to do so.

    REPO_ROOT=`dirname $SINGULARITY_BUILDDEF`
    cp -r $REPO_ROOT/ $SINGULARITY_ROOTFS/planner

%post

    ## The "%post"-part of this script is called after the container has
    ## been created with the "%setup"-part above and runs "inside the
    ## container". Most importantly, it is used to install dependencies
    ## and build the planner. Add all commands that have to be executed
    ## once before the planner runs in this part of the script.

    ## Install all necessary dependencies.
    apt update
    apt -y install cmake g++ g++-multilib make python

    ## Build your planner
    cd /planner
    ./build.py release64 -j4

%runscript
    ## The runscript is called whenever the container is used to solve
    ## an instance.

    DOMAINFILE=$1
    PROBLEMFILE=$2
    PLANFILE=$3

    ## Call your planner.
    /planner/fast-downward.py \
        --transform-task "/planner/builds/release64/bin/preprocess" \
        --build 'release64' \
        --search-memory-limit '7744M' \
        --plan-file $PLANFILE \
        $DOMAINFILE \
        $PROBLEMFILE \
        --symmetries 'sym=structural_symmetries(search_symmetries=oss)' \
        --search 'astar(celmcut,symmetries=sym,pruning=stubborn_sets_simple(minimum_pruning_ratio=0.01),num_por_probes=1000)'

## Update the following fields with meta data about your submission.
## Please use the same field names and use only one line for each value.
%labels
Name        Metis1
Description A remake of Metis that participated in IPC2014. It uses partial order reduction (simple stubborn sets) with a safety belt that turns off pruning if not enough pruning happens and with support for conditional effects, symmetry-based pruning (OSS), the h2 preprocessor of Alcázar and Torralba, and the lmcut heuristic with support for conditional effects.
Authors     Silvan Sievers <silvan.sievers@unibas.ch> and Michael Katz <michael.katz1@ibm.com>
SupportsDerivedPredicates no
SupportsQuantifiedPreconditions no
SupportsQuantifiedEffects no
