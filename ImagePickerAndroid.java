private static Activity me;
private static String imageString = "";
private static boolean activityDone = false;
private static final int IMAGE_PICKER_ACTIVITY = 31;

//in onCreate method add this line :
me = this;
//

public static void openImage()  {
		
	activityDone = false;
		
	Intent intent = new Intent();
	intent.setType("image/*");
	intent.setAction(Intent.ACTION_GET_CONTENT);
	      
	me.startActivityForResult(intent, IMAGE_PICKER_ACTIVITY); //31 is an ID to recognize that intent yourself
}
	
public static String getImageString() {
	if (activityDone)
		return imageString;
	else 
		return "";
}

protected void onActivityResult(int requestCode, int resultCode, Intent data) {

	if (requestCode == IMAGE_PICKER_ACTIVITY) {
		if (resultCode == Activity.RESULT_OK) {
					
			Uri imageUri = data.getData();
	        
			Cursor cursor = getContentResolver().query(imageUri, null, null, null, null); 
	  		cursor.moveToFirst(); 
			int idx = cursor.getColumnIndex(MediaStore.Images.ImageColumns.DATA); 
				
			imageString = cursor.getString(idx); 
		        
		        activityDone = true;
				
		        informNative();
		}
			
		if (resultCode == Activity.RESULT_CANCELED) {
			informNativeCancel();
		}
	}
}//onActivityResult

private native void informNativeCancel();
private native void informNative();
