
void LoopTargetInScreen()
{
    for (AActor* kTarget : ScannedTargets)
    {
        if (ProjectWorldLocationToScreen(kTarget->GetScanPoint(), ScreenLocation)
        && UKismetMathLibrary::InRange_FloatFloat(ScreenLocation.X, 0, ScreenSizeX)
        && UKismetMathLibrary::InRange_FloatFloat(ScreenLocation.Y, 0, ScreenSizeY)
        && HasSigal(kTarget))
        {
            if (!FreeFocusableTargets.Contains(kTarget))
            {
                FreeFocusableTargets.AddUnique(kTarget);
                bFreeFocusableUpdated = true;
            }
        }
        else
        {
            if (FreeFocusableTargets.Contains(kTarget))
            {
                FreeFocusableTargets.Remove(kTarget);
                bFreeFocusableUpdated = true;
            }
        }
    }

    if (FreeFocusableTargets.Num() == 0) return;

    if (bFreeFocusableUpdated)
    {
        FocusableTarget = FindBestTarget(FreeFocusableTargets);
        FreeFocusableCurIdx = 0;
        bFreeFocusableUpdated = false;
    }
    else
    {
        if (FreeFocusableCurIdx < FreeFocusableTargets.Num())
        {
            FocusableTarget = FreeFocusableTargets[FreeFocusableCurIdx];
            FreeFocusableCurIdx = (FreeFocusableCurIdx + 1) % FreeFocusableTargets.Num();
        }
    }

    if (FocusableTarget)
    {
        if (FocusedTarget)
        {
            OnTargetFocusLost(FocusedTarget);
        }

        FocusedTarget = FocusableTarget;
        OnTargetFocused(FocusedTarget);
    }
}
