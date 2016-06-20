<?php
/**
 * @file
 * informea_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function informea_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function informea_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function informea_search_default_search_api_index() {
  $items = array();
  $items['informea_documents'] = entity_import('search_api_index', '{
    "name" : "InforMEA Documents",
    "machine_name" : "informea_documents",
    "description" : null,
    "server" : "solr_4_informea_documents",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "document" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "attachments_field_document_abstract" : { "type" : "text" },
        "attachments_field_document_other" : { "type" : "text" },
        "attachments_field_files" : { "type" : "text" },
        "body:summary" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "created" : { "type" : "date" },
        "field_country" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_document_authors" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_document_identifiers" : {
          "type" : "list\\u003Cinteger\\u003E",
          "entity_type" : "field_collection_item"
        },
        "field_document_type" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_image:alt" : { "type" : "text" },
        "field_image:file" : { "type" : "integer", "entity_type" : "file" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_last_update" : { "type" : "date" },
        "field_sorting_date" : { "type" : "date" },
        "field_sorting_order" : { "type" : "integer" },
        "field_treaty" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "promote" : { "type" : "boolean" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "title_field" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" },
        "uuid" : { "type" : "text" },
        "vid" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_node_status" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_attachments_alter_settings" : {
          "status" : 1,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_attachments_entityreference_alter_settings" : {
          "status" : 0,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "uuid" : true,
              "title_field" : true,
              "field_image:alt" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  $items['informea_fulltext_solr_index'] = entity_import('search_api_index', '{
    "name" : "InforMEA fulltext Solr index",
    "machine_name" : "informea_fulltext_solr_index",
    "description" : "Search index containing MEA content retrieved via OData API",
    "server" : "search_solr_server",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [
          "action_plan",
          "contact_person",
          "country",
          "decision",
          "decision_paragraph",
          "event_calendar",
          "geographical_site",
          "national_report",
          "reporting_obligation_cycle",
          "treaty",
          "treaty_article",
          "treaty_paragraph"
        ]
      },
      "index_directly" : 0,
      "cron_limit" : "10",
      "fields" : {
        "attachments_field_files" : { "type" : "text" },
        "body:summary" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "field_action_plan_type" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_country" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_country_official_name" : { "type" : "text" },
        "field_decision_number" : { "type" : "text" },
        "field_informea_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_informea_tags:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_informea_tags:name_field" : { "type" : "list\\u003Ctext\\u003E", "boost" : "2.0" },
        "field_meeting" : { "type" : "integer", "entity_type" : "node" },
        "field_official_name" : { "type" : "text", "boost" : "2.0" },
        "field_official_publication" : { "type" : "text" },
        "field_region" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_sorting_date" : { "type" : "date" },
        "field_treaty" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "language" : { "type" : "string" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text", "boost" : "21.0" },
        "title_field" : { "type" : "text", "boost" : "21.0" },
        "type" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_attachments_alter_settings" : {
          "status" : 1,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_attachments_entityreference_alter_settings" : {
          "status" : 0,
          "weight" : "0",
          "settings" : {
            "excluded_extensions" : "aif art avi bmp gif ico mov oga ogv png psd ra ram rgb flv",
            "number_indexed" : "0",
            "max_file_size" : "0",
            "excluded_private" : 1
          }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "field_informea_tags:name_field" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "body:value" : true,
              "body:summary" : true,
              "field_informea_tags:name_field" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "field_informea_tags:name_field" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "title_field" : true,
              "field_decision_number" : true,
              "field_official_name" : true,
              "field_informea_tags:name_field" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function informea_search_default_search_api_server() {
  $items = array();
  $items['apache_solr_news_core'] = entity_import('search_api_server', '{
    "name" : "Apache Solr 4 news core",
    "machine_name" : "apache_solr_news_core",
    "description" : "The news core",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr\\/informea-news",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  $items['search_solr_server'] = entity_import('search_api_server', '{
    "name" : "Search Solr server",
    "machine_name" : "search_solr_server",
    "description" : "The Apache Solr search server with InforMEA indexed entities",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "127.0.0.1",
      "port" : "8983",
      "path" : "\\/solr\\/informea",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 1,
      "retrieve_data" : 1,
      "highlight_data" : 1,
      "skip_schema_check" : 0,
      "solr_version" : "4",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  $items['solr_4_informea_documents'] = entity_import('search_api_server', '{
    "name" : "solr 4 informea-documents",
    "machine_name" : "solr_4_informea_documents",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "http",
      "host" : "localhost",
      "port" : "8983",
      "path" : "\\/solr\\/informea-documents",
      "http_user" : "",
      "http_pass" : "",
      "excerpt" : 1,
      "retrieve_data" : 1,
      "highlight_data" : 1,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO"
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
