# Contents
- [the reason of using new and delete](Reasons)
- [the new and delete is static member function](new-delete-member-function)

## reasons
> to detect usage errors  
1. using more than one delete on newed memory.
2. data overruns and underruns  

# new delete member function
> class member function new and delete is static, so you cannot use virtual,  
for non-virtual dstor, the delete statement only delete class father-delete-member in heritance.