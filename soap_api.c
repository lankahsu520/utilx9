/***************************************************************************
 * Copyright (C) 2017 - 2020, Lanka Hsu, <lankahsu@gmail.com>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include "utilx9.h"

#define MAX_OF_WRAP 8192
#define USE_MXML_OPAQUE

char *soap_element_2string(soap_node_t *parent_node)
{
	mxmlSetWrapMargin(MAX_OF_WRAP);
	return mxmlSaveAllocString(parent_node, MXML_NO_CALLBACK);
}

void soap_element_dump(soap_node_t *parent_node)
{
	char *buffer = soap_element_2string(parent_node);
	DBG_LN_Y("(buffer: %s)", buffer );
	SAFE_FREE(buffer);
}

const char *soap_element_name(soap_node_t *parent_node)
{
	return mxmlGetElement(parent_node);
}

void soap_element_print(soap_node_t *curr_node)
{
	if ( (curr_node) && (mxmlGetType(curr_node) == MXML_ELEMENT) )
	{
		DBG_LN_Y("(type: %d)", mxmlGetType(curr_node));

		switch (mxmlGetType(curr_node))
		{
			case MXML_IGNORE:
		 		break;
			case MXML_ELEMENT:
				DBG_LN_Y("	(name: %s)", mxmlGetElement(curr_node));
				if (mxmlGetText(curr_node, NULL))
				{
					DBG_LN_Y("	(text: %s)", mxmlGetText(curr_node, NULL));
				}
				int i = 0;
				for (i = 0; i < curr_node->value.element.num_attrs; i++)
				{
					if (curr_node->value.element.attrs )
					{
						DBG_LN_Y("		(%s=%s)", curr_node->value.element.attrs[i].name, curr_node->value.element.attrs[i].value);
					}
				}
		 		break;
		  case MXML_INTEGER:
		 		break;
			case MXML_OPAQUE:
		 		break;
		  case MXML_REAL:
		 		break;
		  case MXML_TEXT:
				if (curr_node->value.text.string)
				{
					DBG_LN_Y("	(string: %s)",  curr_node->value.text.string);
				}
		 		break;
		  case MXML_CUSTOM:
		 		break;
		}
	}
}

void soap_element_save(soap_node_t *parent_node, char *filename)
{
	FILE *fp = SAFE_FOPEN(filename, "w+");
	if (fp)
	{
		mxmlSetWrapMargin(MAX_OF_WRAP);
		mxmlSaveFile(parent_node, fp, MXML_NO_CALLBACK);
		SAFE_FCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_FOPEN error !!! (%s)", filename );
	}
}


soap_node_t *soap_element_fetch(soap_node_t *parent_node, const char *ns, const char *element, const char *attr, const char *value)
{
	soap_node_t *curr_node = NULL;

	if (parent_node)
	{
		curr_node = mxmlFindElement_ex(parent_node, parent_node, ns, element, attr, value, MXML_DESCEND);
		//curr_node = mxmlFindElement(parent_node, parent_node, element, attr, value, MXML_DESCEND);
	}
	return curr_node;
}

const char *soap_element_attr(soap_node_t *parent_node, const char *name)
{
	return mxmlElementGetAttr(parent_node, name);
}

void soap_element_attr_set(soap_node_t *parent_node, const char *name, const char  *value)
{
	mxmlElementSetAttr(parent_node, name, value);
}

const char *soap_element_text(soap_node_t *parent_node, int *whitespace)
{
#ifdef USE_MXML_OPAQUE	
	return mxmlGetOpaque(parent_node);
#else
	return mxmlGetText(parent_node, whitespace);
#endif
}

void soap_element_text_new(soap_node_t *parent_node, int whitespace, const char *string)
{
	mxmlNewText(parent_node, whitespace, string);
}

void soap_element_text_set(soap_node_t *parent_node, int whitespace, const char *string)
{
#ifdef USE_MXML_OPAQUE	
	mxmlSetOpaque(parent_node, string);
#else
	mxmlSetText(parent_node, whitespace, string);
#endif
}

soap_node_t *soap_element_next_sibling(soap_node_t *parent_node)
{
	return mxmlGetNextSibling(parent_node);
}

soap_node_t *soap_element_1st_child(soap_node_t *parent_node)
{
	return mxmlGetFirstChild(parent_node);
}

soap_node_t *soap_element_add(soap_node_t *parent_node, const char *name)
{
	if (parent_node)
	{
		return mxmlNewElement(parent_node, name);
	}
	return NULL;
}

void soap_element_remove(soap_node_t *parent_node)
{
	if (parent_node)
	{
		mxmlRemove(parent_node);
	}
}

void soap_element_delete(soap_node_t *parent_node)
{
	if (parent_node)
	{
		mxmlDelete(parent_node);
	}
}
	
soap_node_t *soap_load_file(char *filename)
{
	soap_node_t *root_node = NULL;

	FILE *fp = SAFE_FOPEN(filename, "r");
	if (fp)
	{
#ifdef USE_MXML_OPAQUE	
		root_node = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
#else
		root_node = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
#endif
		SAFE_FCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_FOPEN error !!! (%s)", filename );
	}
	return root_node;
}

soap_node_t *soap_load_string(char *xmlbuffer)
{
	if (xmlbuffer)
	{
#ifdef USE_MXML_OPAQUE	
		return mxmlLoadString(NULL, xmlbuffer, MXML_OPAQUE_CALLBACK);
#else
		return mxmlLoadString(NULL, xmlbuffer, MXML_TEXT_CALLBACK);
#endif
	}
	else
	{
		return NULL;
	}
}

void soap_load_request(SoapCtx_t *soap, char *action)
{
	{
		// open file and to xml node
		char filename[LEN_OF_FILENAME256] = "";
		SAFE_SPRINTF(filename, "./%s.xml", action);
		soap->request_node = soap_load_file(filename);
	}
}

void soap_http_access(SoapCtx_t *soap, HttpCtx_t *http_req)
{
	if ((soap) && (soap->request_node) && (http_req) )
	{
		// req_node -> request string 
		http_req->soap_req.request = soap_element_2string(soap->request_node);
		DBG_TR_LN("(request: %s)", http_req->soap_req.request);

		http_request(http_req);

		// response string -> res_node
		soap->response_node = soap_load_string(http_req->soap_req.response);
		DBG_TR_LN("(response: %s)", http_req->soap_req.response);

		http_request_free(http_req);
	}
}

void soap_free(SoapCtx_t *soap)
{
	//http_request_free(soap->http_req);
	//SAFE_FREE(soap->http_req);
	if (soap)
	{
		soap_element_delete(soap->request_node);
		soap_element_delete(soap->response_node);
		SAFE_FREE(soap);
	}
}

SoapCtx_t *soap_create(char *xmlbuffer)
{
	SoapCtx_t *soap = (SoapCtx_t*)SAFE_CALLOC(1, sizeof(SoapCtx_t));
	if (soap)
	{
		soap->request_node = soap_load_string(xmlbuffer);
	}
	return soap;
}

