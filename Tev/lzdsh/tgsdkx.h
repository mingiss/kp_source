

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Tue May 26 09:59:58 2009
 */
/* Compiler settings for .\tgsdkx.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __tgsdkx_h__
#define __tgsdkx_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITextSnapshot_FWD_DEFINED__
#define __ITextSnapshot_FWD_DEFINED__
typedef interface ITextSnapshot ITextSnapshot;
#endif 	/* __ITextSnapshot_FWD_DEFINED__ */


#ifndef __ITextFont_FWD_DEFINED__
#define __ITextFont_FWD_DEFINED__
typedef interface ITextFont ITextFont;
#endif 	/* __ITextFont_FWD_DEFINED__ */


#ifndef __ITextGRABSDK_FWD_DEFINED__
#define __ITextGRABSDK_FWD_DEFINED__
typedef interface ITextGRABSDK ITextGRABSDK;
#endif 	/* __ITextGRABSDK_FWD_DEFINED__ */


#ifndef __ITextItem_FWD_DEFINED__
#define __ITextItem_FWD_DEFINED__
typedef interface ITextItem ITextItem;
#endif 	/* __ITextItem_FWD_DEFINED__ */


#ifndef __TextFont_FWD_DEFINED__
#define __TextFont_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextFont TextFont;
#else
typedef struct TextFont TextFont;
#endif /* __cplusplus */

#endif 	/* __TextFont_FWD_DEFINED__ */


#ifndef __TextGRABSDK_FWD_DEFINED__
#define __TextGRABSDK_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextGRABSDK TextGRABSDK;
#else
typedef struct TextGRABSDK TextGRABSDK;
#endif /* __cplusplus */

#endif 	/* __TextGRABSDK_FWD_DEFINED__ */


#ifndef __TextItem_FWD_DEFINED__
#define __TextItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextItem TextItem;
#else
typedef struct TextItem TextItem;
#endif /* __cplusplus */

#endif 	/* __TextItem_FWD_DEFINED__ */


#ifndef __TextSnapshot_FWD_DEFINED__
#define __TextSnapshot_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextSnapshot TextSnapshot;
#else
typedef struct TextSnapshot TextSnapshot;
#endif /* __cplusplus */

#endif 	/* __TextSnapshot_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ITextSnapshot_INTERFACE_DEFINED__
#define __ITextSnapshot_INTERFACE_DEFINED__

/* interface ITextSnapshot */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextSnapshot;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39606AF2-BC23-4CA0-84FE-2C1EBDD8A958")
    ITextSnapshot : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextSnapshotVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextSnapshot * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextSnapshot * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextSnapshot * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextSnapshot * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextSnapshot * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextSnapshot * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextSnapshot * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITextSnapshot * This,
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITextSnapshot * This,
            /* [retval][out] */ long *Value);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITextSnapshot * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        END_INTERFACE
    } ITextSnapshotVtbl;

    interface ITextSnapshot
    {
        CONST_VTBL struct ITextSnapshotVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextSnapshot_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextSnapshot_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextSnapshot_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextSnapshot_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextSnapshot_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextSnapshot_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextSnapshot_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextSnapshot_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)

#define ITextSnapshot_get_Count(This,Value)	\
    (This)->lpVtbl -> get_Count(This,Value)

#define ITextSnapshot_get__NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> get__NewEnum(This,ppUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextSnapshot_get_Item_Proxy( 
    ITextSnapshot * This,
    /* [in] */ long Index,
    /* [retval][out] */ VARIANT *retval);


void __RPC_STUB ITextSnapshot_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextSnapshot_get_Count_Proxy( 
    ITextSnapshot * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB ITextSnapshot_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ITextSnapshot_get__NewEnum_Proxy( 
    ITextSnapshot * This,
    /* [retval][out] */ IUnknown **ppUnk);


void __RPC_STUB ITextSnapshot_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextSnapshot_INTERFACE_DEFINED__ */


#ifndef __ITextFont_INTERFACE_DEFINED__
#define __ITextFont_INTERFACE_DEFINED__

/* interface ITextFont */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextFont;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35E042D3-503A-43FF-8108-641BDF041E0B")
    ITextFont : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Escapement( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Weight( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsItalic( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsUnderline( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsStrikeOut( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharSet( 
            /* [retval][out] */ BYTE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutPrecision( 
            /* [retval][out] */ BYTE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClipPrecision( 
            /* [retval][out] */ BYTE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Quality( 
            /* [retval][out] */ BYTE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PitchAndFamily( 
            /* [retval][out] */ BYTE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FaceName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextFontVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextFont * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextFont * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextFont * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextFont * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextFont * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextFont * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextFont * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            ITextFont * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            ITextFont * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Escapement )( 
            ITextFont * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ITextFont * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Weight )( 
            ITextFont * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsItalic )( 
            ITextFont * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsUnderline )( 
            ITextFont * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsStrikeOut )( 
            ITextFont * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CharSet )( 
            ITextFont * This,
            /* [retval][out] */ BYTE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutPrecision )( 
            ITextFont * This,
            /* [retval][out] */ BYTE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClipPrecision )( 
            ITextFont * This,
            /* [retval][out] */ BYTE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Quality )( 
            ITextFont * This,
            /* [retval][out] */ BYTE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PitchAndFamily )( 
            ITextFont * This,
            /* [retval][out] */ BYTE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FaceName )( 
            ITextFont * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ITextFontVtbl;

    interface ITextFont
    {
        CONST_VTBL struct ITextFontVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextFont_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextFont_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextFont_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextFont_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextFont_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextFont_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextFont_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextFont_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define ITextFont_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define ITextFont_get_Escapement(This,pVal)	\
    (This)->lpVtbl -> get_Escapement(This,pVal)

#define ITextFont_get_Orientation(This,pVal)	\
    (This)->lpVtbl -> get_Orientation(This,pVal)

#define ITextFont_get_Weight(This,pVal)	\
    (This)->lpVtbl -> get_Weight(This,pVal)

#define ITextFont_get_IsItalic(This,pVal)	\
    (This)->lpVtbl -> get_IsItalic(This,pVal)

#define ITextFont_get_IsUnderline(This,pVal)	\
    (This)->lpVtbl -> get_IsUnderline(This,pVal)

#define ITextFont_get_IsStrikeOut(This,pVal)	\
    (This)->lpVtbl -> get_IsStrikeOut(This,pVal)

#define ITextFont_get_CharSet(This,pVal)	\
    (This)->lpVtbl -> get_CharSet(This,pVal)

#define ITextFont_get_OutPrecision(This,pVal)	\
    (This)->lpVtbl -> get_OutPrecision(This,pVal)

#define ITextFont_get_ClipPrecision(This,pVal)	\
    (This)->lpVtbl -> get_ClipPrecision(This,pVal)

#define ITextFont_get_Quality(This,pVal)	\
    (This)->lpVtbl -> get_Quality(This,pVal)

#define ITextFont_get_PitchAndFamily(This,pVal)	\
    (This)->lpVtbl -> get_PitchAndFamily(This,pVal)

#define ITextFont_get_FaceName(This,pVal)	\
    (This)->lpVtbl -> get_FaceName(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_Height_Proxy( 
    ITextFont * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITextFont_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_Width_Proxy( 
    ITextFont * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITextFont_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_Escapement_Proxy( 
    ITextFont * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITextFont_get_Escapement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_Orientation_Proxy( 
    ITextFont * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITextFont_get_Orientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_Weight_Proxy( 
    ITextFont * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITextFont_get_Weight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_IsItalic_Proxy( 
    ITextFont * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITextFont_get_IsItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_IsUnderline_Proxy( 
    ITextFont * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITextFont_get_IsUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_IsStrikeOut_Proxy( 
    ITextFont * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITextFont_get_IsStrikeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_CharSet_Proxy( 
    ITextFont * This,
    /* [retval][out] */ BYTE *pVal);


void __RPC_STUB ITextFont_get_CharSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_OutPrecision_Proxy( 
    ITextFont * This,
    /* [retval][out] */ BYTE *pVal);


void __RPC_STUB ITextFont_get_OutPrecision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_ClipPrecision_Proxy( 
    ITextFont * This,
    /* [retval][out] */ BYTE *pVal);


void __RPC_STUB ITextFont_get_ClipPrecision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_Quality_Proxy( 
    ITextFont * This,
    /* [retval][out] */ BYTE *pVal);


void __RPC_STUB ITextFont_get_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_PitchAndFamily_Proxy( 
    ITextFont * This,
    /* [retval][out] */ BYTE *pVal);


void __RPC_STUB ITextFont_get_PitchAndFamily_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextFont_get_FaceName_Proxy( 
    ITextFont * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITextFont_get_FaceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextFont_INTERFACE_DEFINED__ */


#ifndef __ITextGRABSDK_INTERFACE_DEFINED__
#define __ITextGRABSDK_INTERFACE_DEFINED__

/* interface ITextGRABSDK */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextGRABSDK;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("95599BC7-8F45-47B4-B6D6-254EC647E1A8")
    ITextGRABSDK : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterSelectionNotify( 
            /* [in] */ INT_PTR hwnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableSelection( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLicense( 
            /* [in] */ BSTR User,
            /* [in] */ BSTR Key) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelection( 
            /* [out] */ INT_PTR *hwnd,
            /* [out] */ RECT *rect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureFromSelection( 
            /* [in] */ INT_PTR hwndTarget,
            /* [in] */ RECT *rect,
            /* [out] */ BSTR *text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CapturePassword( 
            /* [in] */ INT_PTR hwndTarget,
            /* [in] */ POINT ptScreen,
            /* [out] */ BSTR *pwd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureFromHWND( 
            /* [in] */ INT_PTR hwnd,
            /* [out] */ BSTR *text) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ForceStartSelection( 
            /* [in] */ VARIANT_BOOL enable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetupHotkey( 
            /* [in] */ USHORT MainKey,
            /* [in] */ USHORT ExtendedKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureTextSnapshot( 
            /* [in] */ INT_PTR hwnd,
            /* [out] */ ITextSnapshot **snapshot) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureString( 
            /* [in] */ INT_PTR hwnd,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [out] */ BSTR *value,
            /* [out] */ LONG *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCaptureTimeout( 
            /* [in] */ LONG timeout,
            /* [out] */ LONG *oldTimeout) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureFontInfo( 
            /* [in] */ INT_PTR hwnd,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [out] */ ITextFont **ppFont) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHardwareID( 
            /* [out] */ BSTR *bstr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTrialInfo( 
            /* [out] */ LONG *TotalDays,
            /* [out] */ LONG *LeftDays) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextGRABSDKVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextGRABSDK * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextGRABSDK * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextGRABSDK * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextGRABSDK * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextGRABSDK * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextGRABSDK * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextGRABSDK * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RegisterSelectionNotify )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableSelection )( 
            ITextGRABSDK * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLicense )( 
            ITextGRABSDK * This,
            /* [in] */ BSTR User,
            /* [in] */ BSTR Key);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSelection )( 
            ITextGRABSDK * This,
            /* [out] */ INT_PTR *hwnd,
            /* [out] */ RECT *rect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureFromSelection )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwndTarget,
            /* [in] */ RECT *rect,
            /* [out] */ BSTR *text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CapturePassword )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwndTarget,
            /* [in] */ POINT ptScreen,
            /* [out] */ BSTR *pwd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureFromHWND )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwnd,
            /* [out] */ BSTR *text);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ForceStartSelection )( 
            ITextGRABSDK * This,
            /* [in] */ VARIANT_BOOL enable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetupHotkey )( 
            ITextGRABSDK * This,
            /* [in] */ USHORT MainKey,
            /* [in] */ USHORT ExtendedKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureTextSnapshot )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwnd,
            /* [out] */ ITextSnapshot **snapshot);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureString )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwnd,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [out] */ BSTR *value,
            /* [out] */ LONG *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCaptureTimeout )( 
            ITextGRABSDK * This,
            /* [in] */ LONG timeout,
            /* [out] */ LONG *oldTimeout);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureFontInfo )( 
            ITextGRABSDK * This,
            /* [in] */ INT_PTR hwnd,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [out] */ ITextFont **ppFont);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHardwareID )( 
            ITextGRABSDK * This,
            /* [out] */ BSTR *bstr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTrialInfo )( 
            ITextGRABSDK * This,
            /* [out] */ LONG *TotalDays,
            /* [out] */ LONG *LeftDays);
        
        END_INTERFACE
    } ITextGRABSDKVtbl;

    interface ITextGRABSDK
    {
        CONST_VTBL struct ITextGRABSDKVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextGRABSDK_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextGRABSDK_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextGRABSDK_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextGRABSDK_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextGRABSDK_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextGRABSDK_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextGRABSDK_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextGRABSDK_RegisterSelectionNotify(This,hwnd)	\
    (This)->lpVtbl -> RegisterSelectionNotify(This,hwnd)

#define ITextGRABSDK_EnableSelection(This,enable)	\
    (This)->lpVtbl -> EnableSelection(This,enable)

#define ITextGRABSDK_SetLicense(This,User,Key)	\
    (This)->lpVtbl -> SetLicense(This,User,Key)

#define ITextGRABSDK_GetSelection(This,hwnd,rect)	\
    (This)->lpVtbl -> GetSelection(This,hwnd,rect)

#define ITextGRABSDK_CaptureFromSelection(This,hwndTarget,rect,text)	\
    (This)->lpVtbl -> CaptureFromSelection(This,hwndTarget,rect,text)

#define ITextGRABSDK_CapturePassword(This,hwndTarget,ptScreen,pwd)	\
    (This)->lpVtbl -> CapturePassword(This,hwndTarget,ptScreen,pwd)

#define ITextGRABSDK_CaptureFromHWND(This,hwnd,text)	\
    (This)->lpVtbl -> CaptureFromHWND(This,hwnd,text)

#define ITextGRABSDK_ForceStartSelection(This,enable)	\
    (This)->lpVtbl -> ForceStartSelection(This,enable)

#define ITextGRABSDK_SetupHotkey(This,MainKey,ExtendedKey)	\
    (This)->lpVtbl -> SetupHotkey(This,MainKey,ExtendedKey)

#define ITextGRABSDK_CaptureTextSnapshot(This,hwnd,snapshot)	\
    (This)->lpVtbl -> CaptureTextSnapshot(This,hwnd,snapshot)

#define ITextGRABSDK_CaptureString(This,hwnd,x,y,value,index)	\
    (This)->lpVtbl -> CaptureString(This,hwnd,x,y,value,index)

#define ITextGRABSDK_SetCaptureTimeout(This,timeout,oldTimeout)	\
    (This)->lpVtbl -> SetCaptureTimeout(This,timeout,oldTimeout)

#define ITextGRABSDK_CaptureFontInfo(This,hwnd,x,y,ppFont)	\
    (This)->lpVtbl -> CaptureFontInfo(This,hwnd,x,y,ppFont)

#define ITextGRABSDK_GetHardwareID(This,bstr)	\
    (This)->lpVtbl -> GetHardwareID(This,bstr)

#define ITextGRABSDK_GetTrialInfo(This,TotalDays,LeftDays)	\
    (This)->lpVtbl -> GetTrialInfo(This,TotalDays,LeftDays)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_RegisterSelectionNotify_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwnd);


void __RPC_STUB ITextGRABSDK_RegisterSelectionNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_EnableSelection_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ VARIANT_BOOL enable);


void __RPC_STUB ITextGRABSDK_EnableSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_SetLicense_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ BSTR User,
    /* [in] */ BSTR Key);


void __RPC_STUB ITextGRABSDK_SetLicense_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_GetSelection_Proxy( 
    ITextGRABSDK * This,
    /* [out] */ INT_PTR *hwnd,
    /* [out] */ RECT *rect);


void __RPC_STUB ITextGRABSDK_GetSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_CaptureFromSelection_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwndTarget,
    /* [in] */ RECT *rect,
    /* [out] */ BSTR *text);


void __RPC_STUB ITextGRABSDK_CaptureFromSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_CapturePassword_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwndTarget,
    /* [in] */ POINT ptScreen,
    /* [out] */ BSTR *pwd);


void __RPC_STUB ITextGRABSDK_CapturePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_CaptureFromHWND_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwnd,
    /* [out] */ BSTR *text);


void __RPC_STUB ITextGRABSDK_CaptureFromHWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_ForceStartSelection_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ VARIANT_BOOL enable);


void __RPC_STUB ITextGRABSDK_ForceStartSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_SetupHotkey_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ USHORT MainKey,
    /* [in] */ USHORT ExtendedKey);


void __RPC_STUB ITextGRABSDK_SetupHotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_CaptureTextSnapshot_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwnd,
    /* [out] */ ITextSnapshot **snapshot);


void __RPC_STUB ITextGRABSDK_CaptureTextSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_CaptureString_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwnd,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [out] */ BSTR *value,
    /* [out] */ LONG *index);


void __RPC_STUB ITextGRABSDK_CaptureString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_SetCaptureTimeout_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ LONG timeout,
    /* [out] */ LONG *oldTimeout);


void __RPC_STUB ITextGRABSDK_SetCaptureTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_CaptureFontInfo_Proxy( 
    ITextGRABSDK * This,
    /* [in] */ INT_PTR hwnd,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [out] */ ITextFont **ppFont);


void __RPC_STUB ITextGRABSDK_CaptureFontInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_GetHardwareID_Proxy( 
    ITextGRABSDK * This,
    /* [out] */ BSTR *bstr);


void __RPC_STUB ITextGRABSDK_GetHardwareID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextGRABSDK_GetTrialInfo_Proxy( 
    ITextGRABSDK * This,
    /* [out] */ LONG *TotalDays,
    /* [out] */ LONG *LeftDays);


void __RPC_STUB ITextGRABSDK_GetTrialInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextGRABSDK_INTERFACE_DEFINED__ */


#ifndef __ITextItem_INTERFACE_DEFINED__
#define __ITextItem_INTERFACE_DEFINED__

/* interface ITextItem */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("504C46FF-D50A-450D-9754-B17B742E9C46")
    ITextItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bounds( 
            /* [retval][out] */ RECT *bounds) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Window( 
            /* [retval][out] */ INT_PTR *hwnd) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *text) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharactersWidth( 
            /* [retval][out] */ VARIANT *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Spaces( 
            /* [retval][out] */ VARIANT *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ INT *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ INT *retval) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextFont( 
            /* [retval][out] */ ITextFont **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextItem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextItem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextItem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextItem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bounds )( 
            ITextItem * This,
            /* [retval][out] */ RECT *bounds);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Window )( 
            ITextItem * This,
            /* [retval][out] */ INT_PTR *hwnd);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            ITextItem * This,
            /* [retval][out] */ BSTR *text);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CharactersWidth )( 
            ITextItem * This,
            /* [retval][out] */ VARIANT *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spaces )( 
            ITextItem * This,
            /* [retval][out] */ VARIANT *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForeColor )( 
            ITextItem * This,
            /* [retval][out] */ INT *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            ITextItem * This,
            /* [retval][out] */ INT *retval);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextFont )( 
            ITextItem * This,
            /* [retval][out] */ ITextFont **pVal);
        
        END_INTERFACE
    } ITextItemVtbl;

    interface ITextItem
    {
        CONST_VTBL struct ITextItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextItem_get_Bounds(This,bounds)	\
    (This)->lpVtbl -> get_Bounds(This,bounds)

#define ITextItem_get_Window(This,hwnd)	\
    (This)->lpVtbl -> get_Window(This,hwnd)

#define ITextItem_get_Text(This,text)	\
    (This)->lpVtbl -> get_Text(This,text)

#define ITextItem_get_CharactersWidth(This,retval)	\
    (This)->lpVtbl -> get_CharactersWidth(This,retval)

#define ITextItem_get_Spaces(This,retval)	\
    (This)->lpVtbl -> get_Spaces(This,retval)

#define ITextItem_get_ForeColor(This,retval)	\
    (This)->lpVtbl -> get_ForeColor(This,retval)

#define ITextItem_get_BackColor(This,retval)	\
    (This)->lpVtbl -> get_BackColor(This,retval)

#define ITextItem_get_TextFont(This,pVal)	\
    (This)->lpVtbl -> get_TextFont(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_Bounds_Proxy( 
    ITextItem * This,
    /* [retval][out] */ RECT *bounds);


void __RPC_STUB ITextItem_get_Bounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_Window_Proxy( 
    ITextItem * This,
    /* [retval][out] */ INT_PTR *hwnd);


void __RPC_STUB ITextItem_get_Window_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_Text_Proxy( 
    ITextItem * This,
    /* [retval][out] */ BSTR *text);


void __RPC_STUB ITextItem_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_CharactersWidth_Proxy( 
    ITextItem * This,
    /* [retval][out] */ VARIANT *retval);


void __RPC_STUB ITextItem_get_CharactersWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_Spaces_Proxy( 
    ITextItem * This,
    /* [retval][out] */ VARIANT *retval);


void __RPC_STUB ITextItem_get_Spaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_ForeColor_Proxy( 
    ITextItem * This,
    /* [retval][out] */ INT *retval);


void __RPC_STUB ITextItem_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_BackColor_Proxy( 
    ITextItem * This,
    /* [retval][out] */ INT *retval);


void __RPC_STUB ITextItem_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextItem_get_TextFont_Proxy( 
    ITextItem * This,
    /* [retval][out] */ ITextFont **pVal);


void __RPC_STUB ITextItem_get_TextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextItem_INTERFACE_DEFINED__ */



#ifndef __TextGRABSDKLib_LIBRARY_DEFINED__
#define __TextGRABSDKLib_LIBRARY_DEFINED__

/* library TextGRABSDKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TextGRABSDKLib;

EXTERN_C const CLSID CLSID_TextFont;

#ifdef __cplusplus

class DECLSPEC_UUID("A05BBABC-5EE2-43F8-96F2-1B581613E8A4")
TextFont;
#endif

EXTERN_C const CLSID CLSID_TextGRABSDK;

#ifdef __cplusplus

class DECLSPEC_UUID("15CED018-EA43-4CC0-AE44-5E8F413E5578")
TextGRABSDK;
#endif

EXTERN_C const CLSID CLSID_TextItem;

#ifdef __cplusplus

class DECLSPEC_UUID("0DBEDBD6-5561-4AA6-BF71-96A6BF2864F5")
TextItem;
#endif

EXTERN_C const CLSID CLSID_TextSnapshot;

#ifdef __cplusplus

class DECLSPEC_UUID("1FDF1F25-6E7E-4E0B-9697-8D14377C6B0E")
TextSnapshot;
#endif
#endif /* __TextGRABSDKLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


