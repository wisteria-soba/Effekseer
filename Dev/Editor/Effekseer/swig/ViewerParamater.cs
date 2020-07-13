//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 4.0.2
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Effekseer.swig {

public class ViewerParamater : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal ViewerParamater(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(ViewerParamater obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~ViewerParamater() {
    Dispose(false);
  }

  public void Dispose() {
    Dispose(true);
    global::System.GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          EffekseerNativePINVOKE.delete_ViewerParamater(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public int GuideWidth {
    set {
      EffekseerNativePINVOKE.ViewerParamater_GuideWidth_set(swigCPtr, value);
    } 
    get {
      int ret = EffekseerNativePINVOKE.ViewerParamater_GuideWidth_get(swigCPtr);
      return ret;
    } 
  }

  public int GuideHeight {
    set {
      EffekseerNativePINVOKE.ViewerParamater_GuideHeight_set(swigCPtr, value);
    } 
    get {
      int ret = EffekseerNativePINVOKE.ViewerParamater_GuideHeight_get(swigCPtr);
      return ret;
    } 
  }

  public float RateOfMagnification {
    set {
      EffekseerNativePINVOKE.ViewerParamater_RateOfMagnification_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_RateOfMagnification_get(swigCPtr);
      return ret;
    } 
  }

  public bool IsPerspective {
    set {
      EffekseerNativePINVOKE.ViewerParamater_IsPerspective_set(swigCPtr, value);
    } 
    get {
      bool ret = EffekseerNativePINVOKE.ViewerParamater_IsPerspective_get(swigCPtr);
      return ret;
    } 
  }

  public bool IsOrthographic {
    set {
      EffekseerNativePINVOKE.ViewerParamater_IsOrthographic_set(swigCPtr, value);
    } 
    get {
      bool ret = EffekseerNativePINVOKE.ViewerParamater_IsOrthographic_get(swigCPtr);
      return ret;
    } 
  }

  public float FocusX {
    set {
      EffekseerNativePINVOKE.ViewerParamater_FocusX_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_FocusX_get(swigCPtr);
      return ret;
    } 
  }

  public float FocusY {
    set {
      EffekseerNativePINVOKE.ViewerParamater_FocusY_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_FocusY_get(swigCPtr);
      return ret;
    } 
  }

  public float FocusZ {
    set {
      EffekseerNativePINVOKE.ViewerParamater_FocusZ_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_FocusZ_get(swigCPtr);
      return ret;
    } 
  }

  public float AngleX {
    set {
      EffekseerNativePINVOKE.ViewerParamater_AngleX_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_AngleX_get(swigCPtr);
      return ret;
    } 
  }

  public float AngleY {
    set {
      EffekseerNativePINVOKE.ViewerParamater_AngleY_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_AngleY_get(swigCPtr);
      return ret;
    } 
  }

  public float Distance {
    set {
      EffekseerNativePINVOKE.ViewerParamater_Distance_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_Distance_get(swigCPtr);
      return ret;
    } 
  }

  public float ClippingStart {
    set {
      EffekseerNativePINVOKE.ViewerParamater_ClippingStart_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_ClippingStart_get(swigCPtr);
      return ret;
    } 
  }

  public float ClippingEnd {
    set {
      EffekseerNativePINVOKE.ViewerParamater_ClippingEnd_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_ClippingEnd_get(swigCPtr);
      return ret;
    } 
  }

  public bool RendersGuide {
    set {
      EffekseerNativePINVOKE.ViewerParamater_RendersGuide_set(swigCPtr, value);
    } 
    get {
      bool ret = EffekseerNativePINVOKE.ViewerParamater_RendersGuide_get(swigCPtr);
      return ret;
    } 
  }

  public bool IsCullingShown {
    set {
      EffekseerNativePINVOKE.ViewerParamater_IsCullingShown_set(swigCPtr, value);
    } 
    get {
      bool ret = EffekseerNativePINVOKE.ViewerParamater_IsCullingShown_get(swigCPtr);
      return ret;
    } 
  }

  public float CullingRadius {
    set {
      EffekseerNativePINVOKE.ViewerParamater_CullingRadius_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_CullingRadius_get(swigCPtr);
      return ret;
    } 
  }

  public float CullingX {
    set {
      EffekseerNativePINVOKE.ViewerParamater_CullingX_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_CullingX_get(swigCPtr);
      return ret;
    } 
  }

  public float CullingY {
    set {
      EffekseerNativePINVOKE.ViewerParamater_CullingY_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_CullingY_get(swigCPtr);
      return ret;
    } 
  }

  public float CullingZ {
    set {
      EffekseerNativePINVOKE.ViewerParamater_CullingZ_set(swigCPtr, value);
    } 
    get {
      float ret = EffekseerNativePINVOKE.ViewerParamater_CullingZ_get(swigCPtr);
      return ret;
    } 
  }

  public DistortionType Distortion {
    set {
      EffekseerNativePINVOKE.ViewerParamater_Distortion_set(swigCPtr, (int)value);
    } 
    get {
      DistortionType ret = (DistortionType)EffekseerNativePINVOKE.ViewerParamater_Distortion_get(swigCPtr);
      return ret;
    } 
  }

  public RenderMode RenderingMode {
    set {
      EffekseerNativePINVOKE.ViewerParamater_RenderingMode_set(swigCPtr, (int)value);
    } 
    get {
      RenderMode ret = (RenderMode)EffekseerNativePINVOKE.ViewerParamater_RenderingMode_get(swigCPtr);
      return ret;
    } 
  }

  public ViewMode ViewerMode {
    set {
      EffekseerNativePINVOKE.ViewerParamater_ViewerMode_set(swigCPtr, (int)value);
    } 
    get {
      ViewMode ret = (ViewMode)EffekseerNativePINVOKE.ViewerParamater_ViewerMode_get(swigCPtr);
      return ret;
    } 
  }

  public ViewerParamater() : this(EffekseerNativePINVOKE.new_ViewerParamater(), true) {
  }

}

}
