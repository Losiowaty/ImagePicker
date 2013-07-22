
#import "ImagePickerIOS.h"
#import <QuartzCore/QuartzCore.h>
#include "ImagePicker.h"

@implementation ImagePickerIOS

UIWindow *window2;
UIPopoverController *pop;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

-(void) takePicture
{
    window2 = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    [window2 makeKeyAndVisible];
    
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    [imagePicker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    [imagePicker setDelegate:self];
    
    pop = [[UIPopoverController alloc] initWithContentViewController:imagePicker];
    [pop setDelegate:self];
    [pop presentPopoverFromRect:CGRectMake(412, 200, 200, 200) inView:window2 permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    
}

-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    image = [info objectForKey:UIImagePickerControllerOriginalImage];
    [image retain];
    
    [self cleanup];
    
    ImagePicker::ready = true;
}

- (void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController {
    
    ImagePicker::dismissed();
    [self cleanup];
}

-(void) cleanup {
    
    [pop dismissPopoverAnimated:YES];
    [pop release];
    [window2 setHidden:YES];
    [window2 release];
    
}

-(UIImage*) getImage {
    return image;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end