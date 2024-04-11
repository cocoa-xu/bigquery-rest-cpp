# bigquery-rest-cpp
Google BigQuery's REST C++ API.

This is a C++ API for Google BigQuery's REST API. It uses `absl::optional` so that only the fields that are set will be sent to the server.

## Usage
Simply overwrite all files in the `google-cloud-cpp/google/cloud/bigquery/v2/minimal/internal` directory with the files in this repository.

## Why you made this repo?

Google's implementation of BigQuery's REST API by default sends all fields, which causes problems because the default values are different from `(null)` (literally nothing). 

Take the `InsertJobRequest` message as an example, if we only set the `configuration.query.query` and `configuration.query.writeDisposition` field, the following JSON will be sent by this API:

```json
{
  "configuration": {
    "query": {
      "query": "SELECT * FROM dataset_id.table_id LIMIT 5",
      "writeDisposition": "WRITE_TRUNCATE"
    }
  }
}
```

while Google's implementation will serialise all fields with their initial values by default:

> [!NOTE]
> *Google's fix/workaround on this is let you track a list of unset fields, and filter them out, which they have to serialise the JSON object once, and parse it back to a new JSON object as the filter process happens at the parsing stage.*
> 
> *This approach works yet you need to build a full list of available fields first, find and erase the one that is set, and pass the left keys to the callback function.*
> 
> *And the full list of available fields should be copied again so we can use it for the next request, which is not efficient.*

```json
{
  "configuration": {
    "dryRun": false,
    "jobTimeoutMs": "0",
    "jobType": "",
    "query": {
      "allowLargeResults": true,
      "clustering": {
        "fields": []
      },
      "connectionProperties": [],
      "createDisposition": "",
      "createSession": false,
      "defaultDataset": {
        "datasetId": "",
        "projectId": ""
      },
      "destinationEncryptionConfiguration": {
        "kmsKeyName": ""
      },
      "destinationTable": {
        "datasetId": "",
        "projectId": "",
        "tableId": ""
      },
      "flattenResults": false,
      "maximumBytesBilled": "0",
      "parameterMode": "",
      "preserveNulls": false,
      "priority": "",
      "query": "SELECT * FROM dataset_id.table_id LIMIT 5",
      "queryParameters": [],
      "rangePartitioning": {
        "field": "",
        "range": {
          "end": "",
          "interval": "",
          "start": ""
        }
      },
      "schemaUpdateOptions": [],
      "scriptOptions": {
        "keyResultStatement": "",
        "statementByteBudget": "0",
        "statementTimeoutMs": "0"
      },
      "timePartitioning": {
        "expirationTime": "0",
        "field": "",
        "type": ""
      },
      "useLegacySql": false,
      "useQueryCache": false,
      "writeDisposition": "WRITE_TRUNCATE"
    }
  },
  "etag": "",
  "id": "",
  "jobReference": {
    "jobId": "",
    "location": "",
    "projectId": ""
  },
  "kind": "",
  "selfLink": "",
  "statistics": {
    "completionRatio": 0,
    "creationTime": "0",
    "dataMaskingStatistics": {
      "dataMaskingApplied": false
    },
    "endTime": "0",
    "finalExecutionDurationMs": "0",
    "numChildJobs": "0",
    "parentJobId": "",
    "query": {
      "billingTier": 0,
      "cacheHit": false,
      "dclTargetDataset": {
        "datasetId": "",
        "projectId": ""
      },
      "dclTargetTable": {
        "datasetId": "",
        "projectId": "",
        "tableId": ""
      },
      "dclTargetView": {
        "datasetId": "",
        "projectId": "",
        "tableId": ""
      },
      "ddlAffectedRowAccessPolicyCount": "0",
      "ddlOperationPerformed": "",
      "ddlTargetDataset": {
        "datasetId": "",
        "projectId": ""
      },
      "ddlTargetRoutine": {
        "datasetId": "",
        "projectId": "",
        "routineId": ""
      },
      "ddlTargetRowAccessPolicy": {
        "datasetId": "",
        "policyId": "",
        "projectId": "",
        "tableId": ""
      },
      "ddlTargetTable": {
        "datasetId": "",
        "projectId": "",
        "tableId": ""
      },
      "dmlStats": {
        "deletedRowCount": "0",
        "insertedRowCount": "0",
        "updatedRowCount": "0"
      },
      "estimatedBytesProcessed": "0",
      "materializedViewStatistics": {
        "materializedView": []
      },
      "metadataCacheStatistics": {
        "tableMetadataCacheUsage": []
      },
      "numDmlAffectedRows": "0",
      "performanceInsights": {
        "avgPreviousExecutionMs": "0",
        "stagePerformanceChangeInsights": {
          "inputDataChange": {
            "recordsReadDiffPercentage": 0
          },
          "stageId": "0"
        },
        "stagePerformanceStandaloneInsights": {
          "insufficientShuffleQuota": false,
          "slotContention": false,
          "stageId": "0"
        }
      },
      "queryPlan": [],
      "referencedRoutines": [],
      "referencedTables": [],
      "schema": {
        "fields": []
      },
      "searchStatistics": {
        "indexUnusedReasons": [],
        "indexUsageMode": ""
      },
      "statementType": "",
      "timeline": [],
      "totalBytesBilled": "0",
      "totalBytesProcessed": "0",
      "totalBytesProcessedAccuracy": "",
      "totalPartitionsProcessed": "0",
      "totalSlotMs": "0",
      "transferredBytes": "0",
      "undeclaredQueryParameters": []
    },
    "quotaDeferments": [],
    "reservation_id": "",
    "rowLevelSecurityStatistics": {
      "rowLevelSecurityApplied": false
    },
    "scriptStatistics": {
      "evaluationKind": "",
      "stackFrames": []
    },
    "sessionInfo": {
      "sessionId": ""
    },
    "startTime": "0",
    "totalBytesProcessed": "0",
    "totalSlotMs": "0",
    "transactionInfo": {
      "transactionId": ""
    }
  },
  "status": {
    "errorResult": {
      "location": "",
      "message": "",
      "reason": ""
    },
    "errors": [],
    "state": ""
  },
  "user_email": ""
}
```
