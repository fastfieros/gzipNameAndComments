
//This means that things went well
#define ERR_OK                    (0)

//Input errors
#define ERR_INVALID_ARGUMENTS     (10)

//Filesystem errors
#define ERR_NO_FILE               (20)
#define ERR_FILE_READ             (21)
#define ERR_FILE_SEEK             (22)

//GZIP header errors
#define ERR_MAGIC                 (30)
#define ERR_NO_NAME               (31)
#define ERR_NO_COMMENT            (32)
#define ERR_XLEN                  (33)

//System errors
#define ERR_OUT_OF_MEMORY         (40)

//Special value for loop breaking
#define ERR_DONE                  (127)